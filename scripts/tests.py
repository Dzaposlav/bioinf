import os
import resource
import subprocess
import sys
from functools import wraps

EXEC = './bioinf'


def lcp(s):
    n = len(s)
    if n > 10000:
        return
    sa = sorted(list(range(n)), key=lambda i: s[i:])
    return [-1] + [len(os.path.commonprefix([s[sa[i]:], s[sa[i - 1]:]])) for i in range(1, n)] + [-1]


def print_usage():
    rusage = resource.getrusage(resource.RUSAGE_CHILDREN)
    print(f'User time: {rusage.ru_utime}')
    print(f'System time: {rusage.ru_stime}')
    print(f'Max memory usage: {rusage.ru_maxrss}kB')


def usage(f):
    @wraps(f)
    def wrapper(*args, **kwargs):
        usage_before = resource.getrusage(resource.RUSAGE_CHILDREN)
        f(*args, **kwargs)
        usage_after = resource.getrusage(resource.RUSAGE_CHILDREN)

        return {
            'time': usage_after.ru_utime - usage_before.ru_utime,
            'memory': usage_after.ru_maxrss - usage_before.ru_maxrss
        }

    return wrapper


def get_lcp(in_file):
    with open(in_file) as f:
        f.readline()
        s = lcp(''.join(x.strip() for x in f.readlines()) + '$')
        if s is None:
            return
        return str(s).replace(' ', '')


@usage
def test_file(in_file, l):
    if subprocess.run([EXEC, in_file], stdout=subprocess.PIPE).stdout.decode('utf8').strip() != l and l:
        print(f'TEST FAIL - {in_file}')


def main():
    for f in sys.argv[1:]:
        l = get_lcp(f)
        print (test_file(f, l))


if __name__ == '__main__':
    main()
