#!/usr/bin/env python
# encoding: utf-8

import os, sys, difflib, filecmp
from subprocess import Popen, PIPE
from glob import glob

kInputDir = "samples"
kSuffixList = ["decaf", "frag"]

def main():
    try:
        tester = Apter(input_dir=kInputDir, suffix_list=kSuffixList)
        tester.compile()
        tester.run_tests()
    except:
        print "\n"


kDefaultOutSuffix = "out"
kDefaultTesterSuffix = "test"
kDefaultLogFilename = "log.diff"

class Apter:
    __file_comparison_dict = None
    __tester_suffix        = None
    __logfile              = None

    def __init__(self, input_dir, suffix_list,
                 out_suffix=kDefaultOutSuffix,
                 tester_suffix=kDefaultTesterSuffix,
                 log=kDefaultLogFilename):
        self.__tester_suffix = tester_suffix
        self.__logfile       = open(log, 'w')
        input_list           = []
        output_list          = []

        for suffix in suffix_list:
            input_path = os.path.join(input_dir, '*.' + suffix)
            input_list += glob(input_path)

        # locate each file's corresponding output file
        for src_filename in input_list:
            # replace filename's extension with out_suffix
            out_filename = os.path.splitext(src_filename)[0] + '.' + out_suffix

            if (not os.path.exists(out_filename)):
                message = ''.join([
                    "\n*** Warning: Corresponding \'.out\' file for item \'",
                    src_filename, "\' does not exist in input directory \'",
                    input_dir, "\'\n"])
                self.log(message, stdout=True)
                out_filename = None

            output_list.append(out_filename)

        self.__file_comparison_dict = dict(zip(input_list, output_list))


    def __del__(self):
        self.__logfile.flush()
        os.fsync(self.__logfile.fileno())
        self.__logfile.close()


    def run_tests(self):
        self.log("Running " + str(len(self.__file_comparison_dict)) + " tests",
                 emphasis=2, stdout=True, logfile=False)
        failed = 0

        for src_filename in self.__file_comparison_dict:
            # self.log("scanning: " + src_filename, stdout=True)
            test_filename = self.run(src_filename)
            out_filename = self.__file_comparison_dict[src_filename]

            if (out_filename == None):
                continue
            if (filecmp.cmp(test_filename, out_filename)):
                continue

            failed += 1

            df = diff(test_filename, out_filename)
            self.log("\n\n")
            self.log("* failed: " + src_filename, emphasis=2, stdout=True)
            self.__logfile.writelines(df)

        if (failed == 0):
            self.log("\nAll tests were succesful", emphasis=2, stdout=True)
        else:
            print "\nFailed:", failed
            print "See", self.__logfile.name


    def run(self, filename):
        test_filename = os.path.splitext(filename)[0] + '.'
        test_filename = test_filename + self.__tester_suffix

        shell_command = ' '.join(["./dcc <", filename , ">&" , test_filename])
         # >& is both std and stderr

        self.exec_command(shell_command)
        return test_filename


    def compile(self):
        shell_command = ' '.join(["make"])
        self.log("Compiling\n", emphasis=1, stdout=True, logfile=False)
        self.exec_command(shell_command, stdout=True, logfile=False)


    kLogDivider = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
    def log(self, message,
            emphasis=0, divider=False, stdout=False, logfile=True):
        if (message == None):
            return

        if (type(message) != str):
            message = str(message, "utf-8")

        if (stdout):
            print message;

        if (emphasis == 2):
            message = makeHeader(message)

        elif (emphasis == 1):
            message = makeHeader(message, vPadding=0)

        if (logfile):
            self.__logfile.write(message + "\n")
            if (divider):
                self.__logfile.write(self.kLogDivider)


    def exec_command(self, shell_command, stdout=False, logfile=True):
        process = Popen(shell_command, shell=True, stdout=PIPE, stderr=PIPE)
        (stdoutdata, stderrdata) = process.communicate()

        if (stdoutdata):
            self.log(stdoutdata, stdout=stdout, logfile=logfile)

        if (stderrdata):
            self.log(stderrdata, stdout=stdout, logfile=logfile)


def diff(fileA, fileB, context=4):
    with open(fileA, 'r') as f:
        fileA_contents = f.readlines()

    with open(fileB, 'r') as f:
        fileB_contents = f.readlines()

    return difflib.unified_diff(fileA_contents, fileB_contents,
                                fileA, fileB, n=context)


def makeHeader(string, width=78, fChar='=',
               vPadding=1, chSpacing=0, tSpacing=4):
    ts = tSpacing * ' '
    header  = (' ' * chSpacing).join(string).replace('\n', '')
    header = (ts + header + ts).center(width, fChar)

    if(vPadding > 0):
        pad = '\n'.join((fChar * width,) * vPadding)
        prePad  = pad + '\n'
        postPad = '\n' + pad
    else: prePad, postPad = '', ''

    header = prePad + header + postPad

    return header


if __name__ == "__main__":
    sys.exit(main())
