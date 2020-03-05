# -*- coding:utf-8 -*-

import requests
import pprint
import re
import json

url = 'https://leetcode-cn.com/problemset/algorithms/?search=1025'
url = 'https://leetcode-cn.com/problems/api/filter-questions/102'
url = 'https://leetcode-cn.com/api/problems/algorithms/'
r = requests.get(url)
with open("algorithms.json","w") as f:
    f.write(r.text)

dic = dict()
with open("algorithms.json","r") as f:
    dic = json.load(f)

# pp = pprint.PrettyPrinter(indent=4)
# pp.pprint()
id2name = dict()
for one in dic["stat_status_pairs"]:
    id2name[one["stat"]['question_id']] = one["stat"]['question__title_slug']

url = 'https://leetcode-cn.com/problems/'
r = requests.get(url+id2name[100107])

with open("test.html","w") as f:
    f.write(r.text)


'''
{'stat': {'question_id': 100107, 'question__title': 'Guess Numbers', 'question__title_slug': 'guess-numbers', '
question__hide': False, 'total_acs': 17390, 'total_submitted': 21325, 'total_column_articles': 61, 'frontend_qu
estion_id': 'LCP 1', 'is_new_question': False}, 'status': None, 'difficulty': {'level': 1}, 'paid_only': False,
'is_favor': False, 'frequency': 0, 'progress': 0}

'''
