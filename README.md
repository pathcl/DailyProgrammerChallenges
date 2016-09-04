# DailyProgrammerChallenges

This repo contains all of the challenges from [**r/dailyprogrammer**](http://reddit.com/r/dailyprogrammer) and also scripts used to pull challenges from the subreddit 3 times per week and to cleanup directories & remove unnecessary posts 

The [**post-challenges.py**](https://github.com/FreddieV4/DailyProgrammerChallenges/blob/master/post-challenges.py) script is ran via a cron job on a VPS at the end of each week, and then automatically pushes that week's challenges to this repository. The script is pretty inefficient, but it gets the job done. If you see ways to improve it, feel free to submit a pull request and add your name as a contributor.

## Required Modules:
- praw
- subprocess
- re
- os
- pprint

**post-challenges.py runs on Python 3.x**


## Challenges & Solutions

See a missing challenge & missing selftext? Want to add a solution to a challenge? See the [**CONTRIBUTING.md**](https://github.com/FreddieV4/DailyProgrammerChallenges/blob/master/CONTRIBUTING.md) file for how to submit changes.

-------------------------------------
**Creator:** [**Freddie Vargus**](http://github.com/FreddieV4)

Uses the [**MIT License**](https://github.com/FreddieV4/DailyProgrammerChallenges/blob/master/LICENSE)

This project was inspired by [**LewisJohnson**](https://github.com/LewisJohnson/dailyprogrammer), whom I collaborated with on a similar repository.
