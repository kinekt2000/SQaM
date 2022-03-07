import math

# operators = [19,15,8,1,4,4,4,1,12,4,1,1,3,1,2,1] # Pascal
operators = [19,14,5,8,4,4,5,1,1,1,15,4,1,1,1,1,1,2,3,1] # С
# operators = [3,17,3,33,4,7,2,3,1,2,4,4,3,4,6,5,1,2,1,1,1,2,1,2,1,3,1,1,1,1,1]

# operands = [1,1,3,1,3,1,2,2,1,3,7,5,6,3,5,3,4,2,6,2,1] # Pascal
operands = [1,1,3,1,3,1,2,2,3,6,5,6,2,5,3,4,2,6,4] # C
# operands = [26,34,10,7,59,29,3,1,1,1,2,4,4,2,6,5,4,4,2,3,5,18,3,1,5,4,6,3,1,1,2,2,2,1,1,1]


def calc(eta_1, eta_2, N_1, N_2, S, eta_2_a):
    eta = eta_1 + eta_2
    N = N_1 + N_2

    print(f"{eta_1=}")
    print(f"{eta_2=}")
    print(f"{N_1=}")
    print(f"{N_2=}")
    print(f"{eta=}")
    print(f"{N=}")

    theoretical_length          = eta_1*math.log2(eta_1) + eta_2*math.log2(eta_2)
    real_volume                 = N*math.log2(eta)
    potencial_volume            = (2 + eta_2_a)*math.log2(2 + eta_2_a)

    program_level               = potencial_volume / real_volume
    theoretical_program_level   = (2*eta_2)/(eta_1*N)

    intelligence_content        = theoretical_program_level*real_volume
    
    programing_work             = real_volume/program_level

    programing_time             = programing_work/S
    theoretical_programing_time = (eta_1*N_2*N*math.log2(eta))/(2*S*eta_2)
    
    language_level              = program_level*potencial_volume
    expected_errors             = (potencial_volume**2)/(1000*language_level)

    print(f"{theoretical_length=}")
    print(f"{real_volume=}")
    print(f"{potencial_volume=}")
    print(f"{program_level=}")
    print(f"{theoretical_program_level=}")
    print(f"{intelligence_content=}")
    print(f"{programing_work=}")
    print(f"{programing_time=}")
    print(f"{theoretical_programing_time=}")
    print(f"{language_level=}")
    print(f"{expected_errors=}")


calc(len(operators), len(operands), sum(operators), sum(operands), 10, 4)