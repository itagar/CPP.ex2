import sys
import os

# os.system("make")

#test_dir = "./test_examples/"
test_dir = "./testFiles/"
shapes_exec = "Shapes"
SchoolExec = "SchoolSol"

tests_test = os.listdir(test_dir)

for test in tests_test:
    if test.endswith('.in'):
    	os.system("./" + shapes_exec + " " + test_dir + test + " > output")
    	os.system("./" + SchoolExec + " " + test_dir + test + " > outputSchool")
        os.system("echo output:")
        os.system("cat output")
        os.system("echo diff:")
        print('\033[93m')
	os.system("echo "+test_dir + test + ":")
        os.system("diff -s output outputSchool")
        print('\033[92m')

        print("\033[0m\nvalgrind:\033[94m")
        os.system("valgrind --leak-check=full --show-possibly-lost=yes " +
               "--show-reachable=yes --undef-value-errors=yes " +
               "./" + shapes_exec + " " + test_dir + test + " > /dev/null 2> valout")
        os.system("cat valout")
        print("\033[94m\n")


