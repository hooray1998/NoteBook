# -*- coding:utf-8 -*-
import requests



data = {"operationName":"questionData","variables":{"titleSlug":"two-sum"},"query":"query questionData($titleSlug: String!) {\n  question(titleSlug: $titleSlug) {\n    questionId\n    questionFrontendId\n    boundTopicId\n    title\n    titleSlug\n    content\n    translatedTitle\n    translatedContent\n    isPaidOnly\n    difficulty\n    likes\n    dislikes\n    isLiked\n    similarQuestions\n    contributors {\n      username\n      profileUrl\n      avatarUrl\n      __typename\n    }\n    langToValidPlayground\n    topicTags {\n      name\n      slug\n      translatedName\n      __typename\n    }\n    companyTagStats\n    codeSnippets {\n      lang\n      langSlug\n      code\n      __typename\n    }\n    stats\n    hints\n    solution {\n      id\n      canSeeDetail\n      __typename\n    }\n    status\n    sampleTestCase\n    metaData\n    judgerAvailable\n    judgeType\n    mysqlSchemas\n    enableRunCode\n    enableTestMode\n    envInfo\n    book {\n      id\n      bookName\n      pressName\n      description\n      bookImgUrl\n      pressImgUrl\n      productUrl\n      __typename\n    }\n    isSubscribed\n    __typename\n  }\n}\n"}

headers = {
':authority': 'leetcode-cn.com',
':method': 'POST',
':path': '/graphql/',
':scheme': 'https',
'accept': '*/*',
'accept-encoding': 'gzip, deflate, br',
'accept-language': 'zh,zh-CN;q=0.9,en;q=0.8',
'content-length': '1150',
'content-type': 'application/json',
'cookie': '_ga=GA1.2.1028487518.1557243354; gr_user_id=42d24522-2c0a-4f39-b6eb-8d1360b5d4a8; grwng_uid=54172fc3-30fe-4e66-82db-494808300239; _uab_collina=155724352179218687258008; __auc=3a42ce8416e2ee10b3f12906ea0; a2873925c34ecbd2_gr_last_sent_cs1=hoorayitt; Hm_lvt_fa218a3ff7179639febdb15e372f411c=1572744526,1574472427; _gid=GA1.2.649688518.1574472427; csrftoken=9ZvdWjLrzPTXdJHKRBRjEDOJNAwjd2Qxe8sp1lXnBQfis6nivOMX1cSN05cPSvPM; LEETCODE_SESSION=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJfYXV0aF91c2VyX2lkIjoiODQ4ODM2IiwiX2F1dGhfdXNlcl9iYWNrZW5kIjoiYXV0aGVudGljYXRpb24uYXV0aF9iYWNrZW5kcy5QaG9uZUF1dGhlbnRpY2F0aW9uQmFja2VuZCIsIl9hdXRoX3VzZXJfaGFzaCI6IjE2M2E1NjAxNDY1MTlmMTE3NzQ4YzUyMjI2ZDVmYTM1ZGQ0YjMxNGUiLCJpZCI6ODQ4ODM2LCJlbWFpbCI6IiIsInVzZXJuYW1lIjoiaG9vcmF5aXR0IiwidXNlcl9zbHVnIjoiaG9vcmF5aXR0IiwiYXZhdGFyIjoiaHR0cHM6Ly9hc3NldHMubGVldGNvZGUtY24uY29tL2FsaXl1bi1sYy11cGxvYWQvZGVmYXVsdF9hdmF0YXIucG5nIiwicGhvbmVfdmVyaWZpZWQiOnRydWUsInRpbWVzdGFtcCI6IjIwMTktMTEtMjMgMDE6Mjc6MzIuNzEyMDgwKzAwOjAwIiwiUkVNT1RFX0FERFIiOiIxNzIuMjEuNi4yMTUiLCJJREVOVElUWSI6IjMxMWZlZGVjZTcwMDc1NGI2YzBlNDVhM2IzNTIwMDU5IiwiX3Nlc3Npb25fZXhwaXJ5IjoxMjA5NjAwfQ.ZTv3_0ysJHOdMDzdZN2uTCdIqQ7hmVELJHQiGVEwDz4; a2873925c34ecbd2_gr_session_id=89d1182c-b873-4bc5-b6e7-b6924d92aaec; a2873925c34ecbd2_gr_last_sent_sid_with_cs1=89d1182c-b873-4bc5-b6e7-b6924d92aaec; a2873925c34ecbd2_gr_session_id_89d1182c-b873-4bc5-b6e7-b6924d92aaec=true; __asc=dcf62d0c16e96a5ffebdbbbf3fc; Hm_lpvt_fa218a3ff7179639febdb15e372f411c=1574486258; a2873925c34ecbd2_gr_cs1=hoorayitt',
'origin': 'https://leetcode-cn.com',
'referer': 'https://leetcode-cn.com/problems/two-sum/',
'user-agent': 'Opera/9.80 (Windows NT 6.0) Presto/2.12.388 Version/12.14',
'x-csrftoken': '9ZvdWjLrzPTXdJHKRBRjEDOJNAwjd2Qxe8sp1lXnBQfis6nivOMX1cSN05cPSvPM'
}

url = 'https://leetcode-cn.com/graphql/'
r = requests.post(url,data=data,headers=headers)
print(r.text)
