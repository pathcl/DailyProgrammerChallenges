#!/bin/bash

# Author: Freddie Vargus (github.com/FreddieV4)
# Purpose: Automatically pushes changes to repo when post-challenges.py is run
# Sends text to owner to notify about changes


CHANGES="$(git diff --name-only)"

./movedirs.sh

git pull origin master; git add -A; git commit -m "Add challenge(s)"; git push

read -r line < ../mynumber.txt

echo "Repo Successfully Updated with:" $CHANGES | .././twilio-sms.sh -c /.twiliorc/config $line
