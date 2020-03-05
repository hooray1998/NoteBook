# -*- coding:utf-8 -*-
#/usr/bin/env python3

"""
A script to get the self-stats of the leetcode problems
usage: leetcode_stat.py email@example.com password [output_file]
"""

import unicodedata
import sys
from time import sleep

import requests
from bs4 import BeautifulSoup



leetcode_url = 'https://leetcode-cn.com/'

sign_in_url = 'accounts/login/'
sign_in_url = leetcode_url + sign_in_url
submissions_url = 'submissions/'
submissions_url = leetcode_url + submissions_url

sleep_time = 0.5 # sec



def login(email, password):
    client = requests.session()

    while True:
        client.get(sign_in_url)
        csrftoken = client.cookies.keys()
        # csrftoken = client.cookies['x-csrftoken']
        print(csrftoken)
        break
        login_data = {'login': email, 
            'password': password,
            'csrfmiddlewaretoken': csrftoken
        }
        result = client.post(sign_in_url, data=login_data, headers=dict(Referer=sign_in_url))
        
        if result.ok:
            break
        sleep(sleep_time)

    return client



def scrap_tables(client):
    solved_problems = set()
    page_num = 1
    rows = []

    while True:
        if page_num == 1:
            h = client.get(submissions_url)
            #print(h)
        else:
            h = client.get(submissions_url + str(page_num) + '/')
        hbs = BeautifulSoup(h.text, 'html.parser')
        table = hbs.find('table', {'id': 'result-testcases'})
        #print(table)
        if table is None:
            break

        for row in table.find_all('tr'):
            curr_row = row.find_all('td')
            if curr_row == []:
                continue

            time_str = unicodedata.normalize('NFKD', curr_row[0].text).strip()
            problem_str = curr_row[1].find('a')['href'].split('/')[-2]
            accepted_str = curr_row[2].text.strip() # 'Accepted' or not
            lang_str = curr_row[4].text.strip()

            if accepted_str == 'Accepted' and problem_str not in solved_problems:
                solved_problems.add(problem_str)
                curr_row_str = ''
                curr_row_str += '"' + time_str + '", '
                curr_row_str += problem_str + ', '
                curr_row_str += lang_str + ''
                rows.append(curr_row_str)
            
        page_num += 1

    return solved_problems, rows



def output(rows, output_file = 'output.csv'):
    if output_file is None:
        output_file = 'output.csv'
    if not output_file.endswith('.csv'):
        output_file += '.csv'

    rows.insert(0, 'time, problem, languages')
    with open(output_file, 'w') as f:
        f.write('\n'.join(rows))



def main():
    if len(sys.argv) not in (3, 4):
        print('usage: leetcode_stat.py email@example.com password [output_file]')
        return

    email = sys.argv[1]
    password = sys.argv[2]
    output_file = 'output.csv'
    if len(sys.argv) == 4:
        output_file = sys.argv[3]


    print('login')
    client = login(email, password)

    print('start scrapping')
    solved_problems, rows = scrap_tables(client)
    print('end scrapping')

    print('output')
    output(rows, output_file)
    print('finished')



if __name__ == '__main__':
    main()
