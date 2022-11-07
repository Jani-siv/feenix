*** Settings ***
Library    ./Libraries/Framework.py

*** Variables ***
${number1}  ${10}
${number2}  ${20}

*** Test Cases ***
Test 1: Try Ping Local Host
    ${result} =       Ping Test
    Should Be True    ${result}

Test 2: Check Memory Aligment
    ${retval}   Check Elf File Layout    ../arm/src/boot.elf
    Should Be True     ${retval}

*** Keywords ***
Ping Test
    [Documentation]    rpiaddress, targetaddress
    ${result} =        ping local host
    [Return]           ${result}

Check Elf File Layout
    [Arguments]    ${filename}
    ${retval} =         check memory layout elf file    ${filename}
    [Return]    ${retval}
