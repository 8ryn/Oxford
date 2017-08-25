singledo()
{
    fin=$1

    ls $fin

    tag=$2
    outdir=$3

#important to have / after outdir
    outdir=${outdir}/

    mkdir -p $outdir

    cmd="./doAnaeWro.sh ${fin} ${tag} ${outdir} "

    echo ${cmd}
    eval ${cmd}
}

##

dirtag=genData/RFG_a/mergedRFG_a_out_targetC
tt=eWroRFG_a

#Output file 
dd=outdata/eWro
beam=El500;       singledo ${dirtag}_beamel500.root ${tt}_${beam} ${dd}

#beam=El0600;       singledo ${dirtag}_beamel0600.root ${tt}_${beam} ${dd} 
#beam=El1000;       singledo ${dirtag}_beamel1000.root ${tt}_${beam} ${dd}
#beam=El3000;       singledo ${dirtag}_beamel3000.root ${tt}_${beam} ${dd} 
#beam=El6000;       singledo ${dirtag}_beamel6000.root ${tt}_${beam} ${dd} 

#beam=El3000wPiProd; singledo ${dirtag}_beamel3000_pionprodon.root ${tt}_${beam} ${dd}

#beam=El1000rpa1;       singledo ${dirtag}_beamel1000rpa1.root ${tt}_${beam} ${dd}
#beam=El3000rpa1;       singledo ${dirtag}_beamel3000rpa1.root ${tt}_${beam} ${dd}