#!/bin/bash
CC="gcc"
OBJDIR="./Tests/ObjAndCovFiles2"
SW="./SourceCodes/task2.c"
OW="$OBJDIR/task2.o"
W="$OBJDIR/task2"
OPTIONS_CC=" -Wall -Werror -pedantic-errors -Wno-pointer-sign -Wextra -std=gnu11 -ftrapv -g -o"
CHECKMEM="valgrind"
OPTIONS_CHECKMEM="-v --leak-check=full --show-leak-kinds=all"
COPYTESTS="./Tests/ChangedT2"
if [ -z $1 ]
then
    if [ -e $SW ]
    then
        if [ -d $OBJDIR ]
        then
            rm -rf $OBJDIR
        fi
        mkdir $OBJDIR
        $CC $SW -c $OPTIONS_CC $OW --coverage
        $CC $OW $OPTIONS_CC $W --coverage
        echo Run program {y/n}?:
        read ans
        if [ $ans = "y" ]
        then
            if [ -d $OBJDIR ]
            then
                rm -rf $COPYTESTS
            fi
            mkdir $COPYTESTS
            cp -t $COPYTESTS ./Tests/T2/*.txt
            num=0
            $CHECKMEM $OPTIONS_CHECKMEM $W 2>$OBJDIR/valgrind_$num.txt
            touch ./Tests/ChangedT2/exit_read.txt
            chmod -r ./Tests/ChangedT2/exit_read.txt
            for var in $COPYTESTS/*.txt
            do
                num=$[ $num + 1 ]
                $CHECKMEM $OPTIONS_CHECKMEM $W $var 2>$OBJDIR/valgrind_$num.txt
            done
            rm ./Tests/ChangedT2/exit_read.txt
        fi
        echo Run the coverage {y/n}?:
        read answer
        if [ $answer = "y" ]
        then
            if [ -d ./lcov ]
            then
                echo lcov was installed
            else
                echo installing lcov
                git clone https://github.com/linux-test-project/lcov.git
            fi
            ./lcov/bin/lcov --capture --directory $OBJDIR --rc lcov_branch_coverage=1 --output-file $OBJDIR/coverage.info
            ./lcov/bin/genhtml $OBJDIR/coverage.info --branch-coverage -o $OBJDIR
            echo Have you Firefox in your system {y/n}?
            read brows
            if [ $brows = "y" ]
            then
                firefox $OBJDIR/index.html
            fi
        fi	    
    else
        echo You are in wrong direction!!!
    fi
else
    if [ $1 = "clean" ]
    then
        rm -rf $OBJDIR
        rm -rf $COPYTESTS
        if [ -d ./lcov ]
        then
            rm -rf ./lcov
        fi
    else
        echo There is no option $1
    fi
fi

