LCOV=lcov
GENHTML=genhtml

# generate our initial info
"${LCOV}" -d ${PWD}/ -c -o coverage.info

# remove some paths
"${LCOV}" -r coverage.info "*Qt*.framework*" "*Xcode.app*" "*.moc" "*moc_*.cpp" "*/test/*" "/usr/include/c++/*" "/usr/local/include/*" -o coverage-filtered.info

# generate our HTML
"${GENHTML}" coverage-filtered.info -o report/

# reset our counts
"${LCOV}" -d ${PWD}/ -z

