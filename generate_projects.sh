#!/usr/bin/bash

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

echo -n "Is make installed ? "
if ! which 'make' > /dev/null; then
    echo "no"
    echo 'make is not installed, Attempting to install make!'
    sudo apt install make
else
    echo "yes"
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
    git clone $(pwd) $deploy_name
else

    mkdir temp_dir && cd temp_dir && git init && git remote add origin $current_work_dir/$repo_name
    cat << END > Makefile
    .ONESHELL:
    all:
        \techo "Hello world"
END
    git add .
    git commit -m"Temporary Makefile."
    git push origin master
cd .. && rm -fr temp_dir


    echo -e "On Which branch Would you like to set the hooks ?"
    read branch_name
if [[ -z $branch_name ]]; then
    branch_name=master
fi
    cd hooks
    cat << EOF > post-receive
#!/bin/bash

path_bare_dir=\$(pwd)
while read oldrev newrev ref
do
    if [[ \$(echo "\$ref" | sed 's|refs/heads/||') != $branch_name ]]; then
        exit 1
    fi
    echo "Master ref received.  Deploying $branch_name branch to production..."
    if [ ! -d $deploy_name ]; then
        git clone \$path_bare_dir $deploy_name
    else
        git --work-tree=$deploy_name --git-dir=$current_work_dir/$repo_name checkout $branch_name -f
    fi
done
cd $deploy_name
echo -e "You must have a Makefile in your deployment repository!"
make
if [ \$? -ne 0 ]; then
    echo "There is no Makefile"
fi
EOF
chmod 775 'post-receive'
fi
echo "paste 'git clone $(whoami)@$(curl -s ifconfig.me):$current_work_dir/$repo_name' in your terminal"
