*** Settings ***
Library    ./Libraries/Framework.py

*** Variables ***
${number1}  ${10}
${number2}  ${20}

*** Test Cases ***
Test 1: Try Ping Local Host
    ${result} =  Ping Test
    Should Be True    ${result}

*** Keywords ***

Ping Test
    [Documentation]    rpiaddress, targetaddress
    ${result} =      ping local host
    [Return]    ${result}

