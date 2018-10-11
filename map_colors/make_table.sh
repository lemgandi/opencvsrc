#!/bin/bash
# set -x

TABLEFILE=table_tmp.txt

let counter=255

while [ ${counter} -ne 0 ]
do
      echo -n "${counter}, " >> ${TABLEFILE}
      let counter=${counter}-1
      let countermod=${counter}%16
      if [ ${countermod} -eq 0 ]
      then
	  echo >> ${TABLEFILE}
      fi
      
done
echo Tablefile: ${TABLEFILE}
cat ${TABLEFILE}
