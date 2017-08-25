#!/bin/sh

export MYSOFTWARE=/data/t2k/xlu/software

export PYTHIA6=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/pythia6/v6_425/lib/
export LD_LIBRARY_PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/pythia6/v6_425/lib:$LD_LIBRARY_PATH
export LIBXML2_LIB=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/libxml2-2.7.8//install/lib/
export LIBXML2_INC=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/libxml2-2.7.8//install/include/libxml2
export LD_LIBRARY_PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/libxml2-2.7.8//install/lib:$LD_LIBRARY_PATH
export LOG4CPP_INC=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/log4cpp/install/include/
export LOG4CPP_LIB=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/log4cpp/install/lib/
export LD_LIBRARY_PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/log4cpp/install/lib:$LD_LIBRARY_PATH
export LHAPDF_LIB=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/lhapdf-5.8.6//install/lib/
export LHAPDF_INC=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/lhapdf-5.8.6//install/include/
export LHAPATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/lhapdf-5.8.6//install/bin/
export LD_LIBRARY_PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE/lhapdf-5.8.6//install/lib:$LD_LIBRARY_PATH
export ROOTSYS=${MYSOFTWARE}/GENIE/myVersion/install/GENIE//root-5.34.14/root/
export PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE//root-5.34.14/root//bin/:$PATH
export LD_LIBRARY_PATH=${MYSOFTWARE}/GENIE/myVersion/install/GENIE//root-5.34.14/root//lib/:$LD_LIBRARY_PATH

export myNuWro=${MYSOFTWARE}/NuWro/tmp-mv-should-restore-after-using-eWro/nuwro-nuwro11q
#export PATH=$myNuWro/bin:$PATH

export myeWro=${MYSOFTWARE}/eWro/git/
export PATH=$myeWro/bin:$PATH