dir0=$(pwd)

batchtag=b

jobid=0

#

###important
source ${dir0}/myNuWroSetup.sh 

#nrepeat is 1/10 of the official value

#due to isospin, AntiNu RES is reduced
#dirtag=RFG_${batchtag}; nrepeat=50; for ii in $(echo targetC_*Anti*.txt )

dirtag=RFG_${batchtag}; nrepeat=10; for ii in $(echo targetC_beamNuMu*.txt )
do
    for kk in $(seq 1 ${nrepeat})
    do
        dir=${dir0}/outdata/${dirtag}/${dirtag}_out_$(echo ${ii} | awk -F\. '{print $1}')_ID$(echo ${jobid}| awk '{printf("%04d", $jobid)}')

        echo ${dir}
        
        mkdir -p ${dir}
        
        parfile=${dir}/newran${jobid}${ii}
        cat $ii | sed "s:^random_seed=.*:random_seed=${RANDOM}${jobid}:g" >  ${parfile}
        
        cd ${dir}
        
        
        jobfile=${batchtag}${jobid}.sh
###
        cat > ${jobfile} <<EOF

source ${dir0}/myNuWroSetup.sh

cd ${dir}

    job1="$myNuWro/bin/nuwro -i ${parfile} -o out_${dirtag}.root > see_${dirtag}.log"
    echo \$job1
    eval \$job1

###
    job2="$myNuWro/bin/nuwro2rootracker out_${dirtag}.root rtk_${dirtag}.root"
    echo \$job2
    eval \$job2

EOF

###
        chmod +x ${jobfile}
        
        qsub -l cput=00:10:00 -N $jobfile  ./$jobfile
        #./$jobfile 
        
        cd $dir0
        
        jobid=$( expr ${jobid} + 1 )

    done
done


