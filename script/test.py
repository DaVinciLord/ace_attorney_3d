# coding: utf-8
import collections
from collections import OrderedDict

def do_answer(case, cases):
	cases_array = cases[case].split('\n')
	for i in range(0, len(cases_array)):
		line = cases_array[i]
		if '*' in line:
			all_lines = list()
			all_lines.append(line.strip().replace('*', '-'))
			i += 1
			while '*' not in cases_array[i] and '++' not in cases_array[i]:
				all_lines.append(cases_array[i].strip())
				i += 1
				
			for l in all_lines:
				print(l)
			input()
			
	
	
def do_menu(answer, proposition_case):
	options=proposition_case.values()
	while True: 
		i = 1
		for entry in options: 
			print ('{}) {}'.format(i, entry))
			i += 1
		print()
		selection=input("Enter Choice: ")
		print()
		for tmp in proposition_case.keys():
			if selection in tmp:
				return tmp

def do_qcm(qcm_nb):
	qcm_file = open('QCM' + qcm_nb + '.txt')
	lst = [line for line in qcm_file]
	proposition_case = OrderedDict()
	cases = OrderedDict()
	answer = ''
	question = ''
	talk = ''
	for i in range(0, len(lst) - 1):
		if 'TALKING' in lst[i]:
			talk = lst[i + 1].strip()
			i += 1
			
		if 'QUESTION' in lst[i]:
			question = lst[i + 1].strip()
			question_array = question.split('[n]')
			i += 1
			
		if 'ANSWER' in lst[i]:
			answer = lst[i + 1].strip()
			i += 1
			
		if 'PROPOSITION' in lst[i]:
			i += 1
			while lst[i] is not '\n':
				tmp = lst[i].split("->")
				proposition_case[tmp[0]] = tmp[1].strip()
				i += 1
				
		if '[CASE' in lst[i]:
			current_case = lst[i].strip().replace('[', '').replace(']', '')
			cases[current_case] = '' 
			i += 1
			while '//' not in lst[i]:
				cases[current_case] += lst[i]
				i += 1
	
	proposed_answer = ''

		
	while proposed_answer != answer:	
		print('-{}'.format(talk))
		for line in question_array:
			print(line, end='\n')
		print()	
		proposed_answer = do_menu(answer, proposition_case)
		do_answer(proposed_answer, cases)
	
	

f = open('testScript.txt', 'r')
lst = [line for line in f]
qcm_nb = -1
for i in range(0, len(lst)):
	line = lst[i]
	if '*' in line:
		all_lines = list()
		all_lines.append(line.strip().replace('*', '-'))
		i += 1
		while '*' not in lst[i] and '++' not in lst[i]:
			all_lines.append(lst[i].strip())
			i += 1
			
		for l in all_lines:
			print(l)
		input()
		
	if '[QCM]' in line:
		line_list = line.split('->')
		qcm_nb = line_list[1].strip()
		do_qcm(qcm_nb)
		
		i += 1
		

f.close()
