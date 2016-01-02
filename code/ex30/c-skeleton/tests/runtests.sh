echo "Running unit tests:"

# i.e. on Windows we use .exe.... on linux/OSX remove the .exe

for i in tests/*_tests.exe
do
  echo $i
  if test -f $i
  then
    if ./$i 2>> tests/tests.log
    then
      echo $i PASS
    else
      echo "ERROR in test $i: here's tests/tests.log"
      echo "------"
      tail tests/tests.log
      exit 1
    fi
  fi
done

echo ""
