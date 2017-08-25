singledo()
{
    fin=$1

    ls $fin

    tag=$2
    outdir=$3

#important to have / after outdir
    outdir=${outdir}/

    mkdir -p $outdir

    cmd="./doAnaNuWroB.sh ${fin} ${tag} ${outdir} "

    echo ${cmd}
    eval ${cmd}
}

##

dirtag=genData/RFG_b/mergedRFG_b_out_targetC
tt=NuWroRFG_b

#Output file 
dd=outdata/NuWroB

#beam=NuMu3000;       singledo ${dirtag}_beamNuMu3000.root ${tt}_${beam} ${dd}
beam=NuMu1000;       singledo ${dirtag}_beamNuMu1000.root ${tt}_${beam} ${dd} 

#beam=NuMu6000;       singledo ${dirtag}_beamNuMu6000.root ${tt}_${beam} ${dd}
#beam=NuMu600;       singledo ${dirtag}_beamNuMu600.root ${tt}_${beam} ${dd} 

#beam=NuMu3000rpa1;       singledo ${dirtag}_beamNuMu3000rpa1.root ${tt}_${beam} ${dd}
beam=NuMu1000rpa1;       singledo ${dirtag}_beamNuMu1000rpa1.root ${tt}_${beam} ${dd}

#beam=NuMu1000SF;       singledo ${dirtag}_beamNuMu1000SF.root ${tt}_${beam} ${dd} 

#beam=NuMu1000LFG;       singledo ${dirtag}_beamNuMu1000LFG.root ${tt}_${beam} ${dd} 