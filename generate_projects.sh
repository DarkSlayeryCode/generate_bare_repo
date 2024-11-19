#!/bin/sh

current_work_dir=$(pwd)

if ! which 'git' > /dev/null; then
        echo -e "Installing git because it is not installed but it's necessary"
        sudo apt-get install git || sudo yum install git || sudo dnf install git
fi
echo "Enter your project's repository name:"
while :
    do
        read repo_name
        if [[ -z "$repo_name" ]]; then
            echo "Project's repository name cannot be empty"
        else
            break
        fi
done

echo "Enter your deployment repository name:"
read deploy_name
if [[ -z "$deploy_name" ]]; then
    echo "Using the default deployment repository name since it was not provided!"
    deploy_name=deployment/$repo_name
fi

mkdir $repo_name && cd $repo_name && git init --bare

echo -e "Would you like to set CI/CD?\n(Yes/No)..."
while :
    do
        read response
        response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
        if [[ -z "$response" ]]; then
            echo "The response cannot be empty"
        elif [[ "$response" != "yes"  && "$response" != "no" ]]; then
            echo -e "The response can either be \"Yes\" or \"No\""
        else
            break
        fi
    done

if [[ "$response" = "no" ]]; then
    git clone $(pwd) $current_work_dir/$deploy_name
else
    echo -e "On Which branch Would you like to set the hooks ?"
    read branch_name
if [[ -z $branch_name ]]; then
    branch_name=master
fi
    cd hooks
    cat << EOF > post-receive
#!/bin/bash

path_bare_dir=\$(pwd)
if [ ! -d $deploy_name ]; then
    git clone \$path_bare_dir $deploy_name
else
    while read oldrev newrev ref
    do
        if [[ \$ref =~ .*/$branch_name$ ]]; then
            echo "Master ref received.  Deploying master branch to production..."
            if ! git branch --list "$branch_name" > /dev/null; then
                git --work-tree=$deploy_name --git-dir=$current_work_dir/$repo_name checkout -b $branch_name
            else
                git --work-tree=$deploy_name --git-dir=$current_work_dir/$repo_name checkout $branch_name -f
            fi
        else
            echo "Ref $ref successfully received.  Doing nothing: only the master branch may be deployed on this server."
        fi
    done
fi
cd $deploy_name
echo -ne "You must have a Makefile in your deployment repository!"
make
if [ $? -ne 0 ]; then
    echo "There are no Makefile"
fi
EOF
chmod 775 'post-receive'
fi
echo "paste 'git clone $(whoami)@$(curl -s ifconfig.me):$current_work_dir/$repo_name' in your terminal"
