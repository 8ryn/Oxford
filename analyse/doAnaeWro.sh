date

root -b -l <<EOF
.L style.cxx+
.L readeWro.C+
readeWro t
t.DoAnalysis("$1","$2","$3")
.q
EOF

date

