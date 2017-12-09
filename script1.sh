#!/bin/bash
CC="gcc"
OBJDIR="./Tests/ObjAndCovFiles1"
SW=."/SourceCodes/task1.c"
SOW="$OBJDIR/t1.o"
MW="./Tests/main.c"
MOW="$OBJDIR/main.o"
AFW="./Tests/advanced_func.c"
AFOW="$OBJDIR/advanced_func.o"
OW="$OBJDIR/task1"
OPTIONS_CC=" -Wall -Werror -pedantic-errors -Wno-pointer-sign -Wextra -std=gnu11 -ftrapv -g -o"
CHECKMEM="valgrind"
OPTIONS_CHECKMEM="-v --leak-check=full --show-leak-kinds=all"

if [ -z $1 ]
then
    if [ -e $SW ]
    then
        mkdir $OBJDIR
        if [ $MW -nt $MOW ]
        then
            $CC $MW -I./Tests/ -c $OPTIONS_CC $MOW --coverage
        fi
        if [ $SW -nt $SOW ]
        then 
            $CC $SW -I./Tests/ -c $OPTIONS_CC $SOW --coverage
        fi
        if [ $AFW -nt $AFOW ]
        then
            $CC $AFW -I./Tests -c $OPTIONS_CC $AFOW --coverage
        fi
        $CC $MOW $SOW $AFOW $OPTIONS_CC $OW --coverage
        echo Run program {y/n}?:
        read ans
        if [ $ans = "y" ]
        then
            $CHECKMEM $OPTIONS_CHECKMEM $OW 2>$OBJDIR/$CHECKMEM.txt
        fi
        echo Run the coverage {y/n}?:
        read answer
        if [ $answer = "y" ]
        then
            if [ -d lcov]
            then
                echo lcov was installed
            else
                echo installing lcov
                git clone https://github.com/linux-test-project/lcov.git
            fi
            lcov --capture --directory $OBJDIR --rc lcov_branch_coverage=1 --output-file $OBJDIR/coverage.info
            genhtml $OBJDIR/coverage.info --branch-coverage -o $OBJDIR
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
        if [ -d lcov ]
        then
            rm -rf ./lcov
        fi
    else
        echo There is no option $1
    fi
fi
