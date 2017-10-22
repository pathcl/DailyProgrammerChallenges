#!/usr/bin/env python3

"""
Author: Tyler Nivin
Github: github.com/twn346
File: transform.py
Purpose: Used to rename directories to fit a specific naming scheme
i.e. Challenge 0001 - {challenge title}
"""

import glob
import os
import re

# This script will run on the Easy Medium and Hard directories.


def update_challenge_dir_name(oldName, difficulty):
    '''Update the specified challenge dirs names. Returns original name if it
    suspects that it would fail a valid transformation.'''

    # Find the challenge number:
    #  tokens, delimited by ' '
    #  find the first token that has one number embedded within
    #   This should be the challenge number
    #     This should avoid other strings with multiple numbers e.g. '[2016-05-20]'
    tokens = oldName.split()

    currNum = ''
    n = 0
    while (len(tokens) > 0 and n == 0):
        a_token = tokens.pop(0)
        match = re.findall(r'(\d{1,5})', a_token)
        if (match and len(match) == 1):
            currNum = match[0]
            n = len(currNum)

    # Clean up submissions with leading zeros
    if (a_token[0] == '#' and n != 0 and currNum[0] == '0'):
        currNum = currNum[1:]
        n = n - 1

    # No correct looking number found, or, it appears that the
    #   number returned already appears to be in canonical form
    if (n == 0 or currNum[0] == '0'):
        return oldName
          
    # Found a likely looking number
    #   tokens now possess' the remaining title
    #   a_token now has the original and possible multiple iteration number
    #     such as 166b
    i = re.findall(r'\S*' + re.escape(currNum) + '(\S*)$', a_token)
    newNum = ' ' + '0'*(4-n) + currNum + (i.pop() if (len(i) > 0) else ' ') + ' '

    # Construct new title
    newTitle = 'Challenge' + newNum + difficulty.capitalize() + ' - '

    suffix = " ".join([w for w in tokens
        if len(re.findall(r'' +
                      '\[' + difficulty + '|' +
                      currNum + '|' +
                     'challenge',
                     w, re.IGNORECASE)) == 0])

    return newTitle + suffix


def main():

    levels = ['easy', 'intermediate', 'hard']

    for level in levels:
        rawChallengeNames = glob.glob(os.path.join(level + ' Challenges/*'))

        numCharsToRemove = len(level + ' Challenges/')

        # remove the directory from the name
        challengeNames = list(map(lambda x: x[numCharsToRemove:],
                                  rawChallengeNames))

        parent_dir = level.capitalize() + ' Challenges/'

        for each in challengeNames:
            if each != update_challenge_dir_name(each, level):
                os.renames(parent_dir + each,
                           parent_dir + update_challenge_dir_name(each, level))
               #  print(each + ' <::> ' + update_challenge_dir_name(each, level))
        print(level.capitalize() + ' Challenges!')
    return

if __name__ == '__main__':
    main()
