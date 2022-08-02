#!/bin/bash

RED="\e[1;31m"
GREEN="\e[1;32m"
PURPLE="\e[1;35m"
CYAN="\e[1;36m"
RESET="\e[0m"

TEST="../monitoring |& grep monitoring"

PASSED=0
TOTAL=0
COUNT=0

check_valid () {
	COUNT=$((COUNT + 1))
	printf "${CYAN}($COUNT)${RESET} ${PURPLE}$1${RESET}"
	if [[ ! -z $2 ]]; then
		printf "${RED}FAILED\n${RESET}"
	else
		printf "${GREEN}PASSED\n${RESET}"
		PASSED=$((PASSED + 1))
	fi
	printf "${PURPLE}Output:${RESET} $2\n\n"
	TOTAL=$((TOTAL + 1))
}

check_invalid () {
	COUNT=$((COUNT + 1))
	printf "${CYAN}($COUNT)${RESET} ${PURPLE}$1${RESET}"
	if [[ -z $2 ]]; then
		printf "${RED}FAILED\n${RESET}"
	else
		printf "${GREEN}PASSED\n${RESET}"
		PASSED=$((PASSED + 1))
	fi
	printf "${PURPLE}Output:${RESET} $2\n\n"
	TOTAL=$((TOTAL + 1))
}

make -C ../
printf "${CYAN}\n-----------{ Starting tests }------------\n${RESET}"

##############################
#####     VALID FILE     #####
##############################
# printf "${CYAN}\n=== Valid configurations:\n${RESET}"
# cp valid_configs/valid-config monitoring.db
# check_valid "Testing valid config file... " "$(eval "$TEST")"

###################################
#####     INVALID COLUMNS     #####
###################################
printf "${CYAN}\n=== Invalid columns:\n${RESET}"
COUNT=0
cp invalid_configs/bad-http-many-columns monitoring.db # (1)
check_invalid "Testing too many HTTP columns... " "$(eval "$TEST")"

cp invalid_configs/bad-http-few-columns monitoring.db # (2)
check_invalid "Testing too few HTTP columns... " "$(eval "$TEST")"

cp invalid_configs/bad-ping-many-columns monitoring.db # (3)
check_invalid "Testing too many PING columns... " "$(eval "$TEST")"

cp invalid_configs/bad-ping-few-columns monitoring.db # (4)
check_invalid "Testing too few PING columns... " "$(eval "$TEST")"

cp invalid_configs/bad-dns-many-columns monitoring.db # (5)
check_invalid "Testing too many DNS columns... " "$(eval "$TEST")"

cp invalid_configs/bad-dns-few-columns monitoring.db # (6)
check_invalid "Testing too few DNS columns... " "$(eval "$TEST")"

####################################
#####     INVALID PROTOCOL     #####
####################################
printf "${CYAN}\n=== Invalid protocols:\n${RESET}"
COUNT=0
cp invalid_configs/bad-protocol-1 monitoring.db # (1)
check_invalid "Testing invalid protocol REKT... " "$(eval "$TEST")"

cp invalid_configs/bad-protocol-2 monitoring.db # (2)
check_invalid "Testing invalid protocol dns... " "$(eval "$TEST")"

cp invalid_configs/bad-protocol-3 monitoring.db # (3)
check_invalid "Testing invalid protocol PlNG... " "$(eval "$TEST")"

cp invalid_configs/bad-protocol-4 monitoring.db # (4)
check_invalid "Testing invalid protocol HTTTP... " "$(eval "$TEST")"

cp invalid_configs/bad-protocol-5 monitoring.db # (5)
check_invalid "Testing invalid protocol LUL... " "$(eval "$TEST")"

cp invalid_configs/bad-protocol-6 monitoring.db # (6)
check_invalid "Testing invalid protocol POG... " "$(eval "$TEST")"

####################################
#####     INVALID INTERVAL     #####
####################################
printf "${CYAN}\n=== Invalid intervals:\n${RESET}"
COUNT=0
cp invalid_configs/bad-interval-1 monitoring.db # (1)
check_invalid "Testing invalid interval 6a0... " "$(eval "$TEST")"

cp invalid_configs/bad-interval-2 monitoring.db # (2)
check_invalid "Testing invalid interval 12O... " "$(eval "$TEST")"

cp invalid_configs/bad-interval-3 monitoring.db # (3)
check_invalid "Testing invalid interval 5O0... " "$(eval "$TEST")"

##################################
#####     INVALID METHOD     #####
##################################
printf "${CYAN}\n=== Invalid HTTP methods:\n${RESET}"
COUNT=0
cp invalid_configs/bad-method-1 monitoring.db # (1)
check_invalid "Testing invalid method POG... " "$(eval "$TEST")"

cp invalid_configs/bad-method-2 monitoring.db # (2)
check_invalid "Testing invalid method LUL... " "$(eval "$TEST")"

cp invalid_configs/bad-method-3 monitoring.db # (3)
check_invalid "Testing invalid method KEKW... " "$(eval "$TEST")"

cp invalid_configs/bad-method-4 monitoring.db # (4)
check_invalid "Testing invalid method 42... " "$(eval "$TEST")"

cp invalid_configs/bad-method-5 monitoring.db # (5)
check_invalid "Testing invalid method (whitespace)... " "$(eval "$TEST")"

cp invalid_configs/bad-method-6 monitoring.db # (6)
check_invalid "Testing invalid method P0ST... " "$(eval "$TEST")"

################################
#####     INVALID CODE     #####
################################
printf "${CYAN}\n=== Invalid HTTP codes:\n${RESET}"
COUNT=0
cp invalid_configs/bad-code-1 monitoring.db # (1)
check_invalid "Testing invalid code 20a0... " "$(eval "$TEST")"

cp invalid_configs/bad-code-2 monitoring.db # (2)
check_invalid "Testing invalid code (whitespace)... " "$(eval "$TEST")"

cp invalid_configs/bad-code-3 monitoring.db # (3)
check_invalid "Testing invalid code abc... " "$(eval "$TEST")"

cp valid_configs/valid-config monitoring.db # restore original monitoring.db

printf "${CYAN}\n---------{ Passed %d out of %d }---------\n\n${RESET}" $PASSED $TOTAL

if [ $PASSED -ne $TOTAL ]; then
	exit 1
fi
