singledo()
{
    fin=$1

    ls $fin

    tag=$2
    outdir=$3
    isexpmode=$4
    protonThres=$5
    otherThres=$6
    dpttwidth=$7

#important to have / after outdir
    outdir=${outdir}/

    mkdir -p $outdir

    cmd="./doAnaNuWro.sh ${fin} ${nQEtoread} ${nREStoread} ${tag} ${outdir} ${isexpmode} ${protonThres} ${otherThres} ${dpttwidth}"

    echo ${cmd}
    eval ${cmd}
}

##

nQEtoread=1000000
nREStoread=0

dirtag=genData/RFG_b/mergedRFG_b_out_targetC
tt=NuWroRFG_b

dd=outdata/NuWro

beam=NuMuB3000;       singledo ${dirtag}_beamNuMu3000.root ${tt}_${beam} ${dd} 0 -999 -999 -999
beam=NuMuB3000rpa1;       singledo ${dirtag}_beamNuMu3000rpa1.root ${tt}_${beam} ${dd} 0 -999 -999 -999



