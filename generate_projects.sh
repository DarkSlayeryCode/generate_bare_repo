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

echo -e "\n\n\t\t\t'$current_work_dir/$deploy_name'\n\n"

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
            while :
                do
                    read branch_name
                    if [[ -n "$branch_name" ]]; then
                        echo "This branch doesn't exist. Would you like to create it ? (Y/N)"
                        read answer
                        if [[ $answer = 'Y' || $answer = 'y' ]]; then
                            git branch $answer
                            break
                        else
                            echo -n "The branch you're trying to use doesn't exist."
                            echo "Choose between '$exist_brc' (the existing branches) or create a new branch"
                        fi
                    else
                        break
                    fi
                done

    cd hooks
    cat << EOF > post-receive
    #!/bin/bash

    path_bare_dir=\$(pwd)
    if [ ! -d $current_work_dir/$deploy_name ]; then
        git clone \$path_bare_dir $current_work_dir/$deploy_name
    else
        while read oldrev newrev ref
        do
            if [[ $ref =~ .*/master$ ]]; then
                echo "Master ref received.  Deploying master branch to production..."
                git --work-tree=$current_work_dir/$deploy_name --git-dir=$current_work_dir/$repo_name checkout $branch_name -f
            else
                echo "Ref $ref successfully received.  Doing nothing: only the master branch may be deployed on this server."
            fi
        done
        fi
EOF
chmod 775 'post-receive'
fi
echo "paste 'git clone $(whoami)@$(curl ifconfig.me):$current_work_dir/$repo_name' in your terminal"
