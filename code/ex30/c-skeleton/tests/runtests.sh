echo "Running unit tests:"

# i.e. on Windows, add .exe

for i in tests/*_tests
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
