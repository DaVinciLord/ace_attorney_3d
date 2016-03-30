import collections

def do_menu(answer, proposition_case):
	while True: 
		options=proposition_case.keys()
		options.sort()
		for entry in options: 
			print ("%s, %s", entry, proposition_case[entry])

		selection=raw_input("Please Select:") 
		if selection =='1': 
			print ("add") 
		elif selection == '2': 
			print ("delete")
		elif selection == '3':
			print ("find") 
		elif selection == '4': 
			break
		else: 
			print ("Unknown Option Selected!") 

def do_qcm(qcm_nb):
	qcm_file = open('QCM' + qcm_nb + '.txt')
	lst = [line for line in qcm_file]
	proposition_case = dict()
	answer = ''
	question = ''
	propositions = dict()
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
	print(proposition_case)
	
	
	do_menu(answer, proposition_case)
	
	
	

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
