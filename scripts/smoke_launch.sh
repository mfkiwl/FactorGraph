set -e
make -s -j 4
factor_graph_main/factor_graph_main | sed "s/^/[factor_graph_main] /"
(exit ${PIPESTATUS[0]})
qbf_solve/qbf_solve | sed "s/^/[qbf_solve] /"
(exit ${PIPESTATUS[0]})
mkdir -p temp
blif_solve/blif_solve --verbosity DEBUG --under_approximating_method ExactAndAccumulate --over_approximating_method FactorGraphApprox --diff_output_path temp/simple_and.dimacs test/data/simple_and.blif | grep -v sec | tee temp/simple_and.out | sed "s/^/[blif_solve] /"
diff temp/simple_and.out test/expected_outputs/simple_and.out
diff temp/simple_and.dimacs test/expected_outputs/simple_and.dimacs
rm -rf temp
echo "[blif_solve diff] SUCCESS"
mkdir temp
test/test | sed "s/^/[test] /"
(exit ${PIPESTATUS[0]})
diff temp/testCnfDump.dimacs test/expected_outputs/testCnfDump.dimacs
echo [testCnfDump] counting number of solutions
cat temp/testCnfDump.dimacs | scripts/approxmc.sh | grep "Number of solutions" > temp/testCnfDump.scalmc
echo [testCnfDump] $(cat temp/testCnfDump.scalmc)
diff temp/testCnfDump.scalmc test/expected_outputs/testCnfDump.scalmc
echo [testCnfDump] SUCCESS
rm -rf temp
echo
echo SUCCESS
