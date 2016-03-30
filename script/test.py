# coding: utf-8
import collections
from collections import OrderedDict

def do_answer(case, cases):
	cases_array = cases[case].split('[n]')
	for line in cases_array:
		print(line, end='\n')

def do_menu(answer, proposition_case):
	while True: 
		options=proposition_case.keys()
		i = 1
		for entry in options: 
			print ('{}) {}'.format(i, entry))
			i += 1
		selection=input("Enter Choice: ") 
		return selection

def do_qcm(qcm_nb):
	qcm_file = open('QCM' + qcm_nb + '.txt')
	lst = [line for line in qcm_file]
	proposition_case = OrderedDict()
	cases = OrderedDict()
	answer = ''
	question = ''
	for i in range(0, len(lst) - 1):
		if 'QUESTION' in lst[i]:
			question = lst[i + 1].strip()
			question_array = question.split('[n]')
			for line in question_array:
				print(line, end='\n')
			i += 1
			
		if 'PROPOSITION' in lst[i]:
			i += 1
			while lst[i] is not '\n':
				tmp = lst[i].split("->")
				proposition_case[tmp[0]] = tmp[1].strip()
				i += 1
				
		if '[CASE' in lst[i]:
			current_case = lst[i].strip()
			cases[current_case] = '' 
			i += 1
			while '//' not in lst[i]:
				cases[current_case] += lst[i].replace('\n', '[n]')
				i += 1
	selection = do_menu(answer, proposition_case)
	print(cases.keys());
	do_answer(proposition_case[selection], cases)

	
	

f = open('testScript.txt', 'r')
lst = [line for line in f]
qcm_nb = -1
for line in lst:
	if '[QCM]' in line:
		line_list = line.split('->')
		qcm_nb = line_list[1].strip()
		print(qcm_nb, end='\n')
		do_qcm(qcm_nb)
f.close()
