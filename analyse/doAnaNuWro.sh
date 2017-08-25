date

root -b -l <<EOF
.L style.cxx+
.L readNuWro.C+
readNuWro t
t.DoAnalysis("$1",$2,$3, "$4", "$5", $6, $7, $8, $9)
.q
EOF

date

