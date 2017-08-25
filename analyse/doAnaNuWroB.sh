date

root -b -l <<EOF
.L style.cxx+
.L readNuWroB.C+
readNuWroB t
t.DoAnalysis("$1","$2","$3")
.q
EOF

date

