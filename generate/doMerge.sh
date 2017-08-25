#call from e.g. outdata/RFG_a/, do 
#../../doMerge.sh RFG_a_out_targetC_beam

dirtag=$1

echo $dirtag

read bb

tmpfile=tmptag
cat > ${tmpfile} <<EOF
EOF

for ii in $(echo ${dirtag}*)
do 
    jj=$(echo $(dirname $(echo $ii| tr -s '_' '/')) | tr -s '/' '_')
    #echo $jj
    echo $jj >> ${tmpfile}
done

echo
echo sorting...
bb=$(cat ${tmpfile} | sort -u )
echo $bb
echo merging...

#exit

for ii in $bb
do
    echo
    echo $ii
    hadd merged${ii}.root ${ii}_ID*/rtk* > seehadd${ii}.log
    echo merging $ii done.
    echo
done
