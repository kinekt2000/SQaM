import sys
import os
import shutil

if __name__ == "__main__":
    if (len(sys.argv) < 4):
        print("Program should take 3 arguments")
        exit(0)

    code_path = sys.argv[1]
    n_runs = int(sys.argv[2])
    n_skip = int(sys.argv[3])

    output_dir = os.path.splitext(os.path.basename(sys.argv[1]))[0]
    cwd = os.getcwd()

    # create output dir
    shutil.rmtree(output_dir, True)
    os.mkdir(output_dir)

    # compile code
    print("code compile...")
    executable_file_name = f"{os.path.basename(code_path)}.out"
    print(f"gcc -o {os.path.join(output_dir, executable_file_name)} {code_path} -lm -I Sampler/libsampler/ -L Sampler/build/libsampler -lsampler")
    os.system(f"gcc -o {os.path.join(output_dir, executable_file_name)} {code_path} -lm -I Sampler/libsampler/ -L Sampler/build/libsampler -lsampler")
    print("code compiled!\n")

    print(f"cd {output_dir}")
    os.chdir(output_dir)
    print("")

    # loop program
    print("program process...")
    print(f"taskset -c 0 ../Sampler/build/tools/sampler-repeat {n_runs} {n_skip} ./{executable_file_name}")
    os.system(f"taskset -c 0 ../Sampler/build/tools/sampler-repeat {n_runs} {n_skip} ./{executable_file_name}")
    
    print(f"python3 ../Sampler/tools/process.py sampler.out > {output_dir}.json")
    os.system(f"python3 ../Sampler/tools/process.py sampler.out > {output_dir}.json")
    print("program processed!\n")

    # render graph
    print("render...")
    print(f"python3 ../Sampler/tools/fmtdot.py < {output_dir}.json | dot -Tpng -s96 > {output_dir}.png")
    os.system(f"python3 ../Sampler/tools/fmtdot.py < {output_dir}.json | dot -Tpng -s96 > {output_dir}.png")
    print("rendered!\n")

    # make odt table
    print("Generating ODT...")
    print(f"python3 ../Sampler/tools/fmttable.py < {output_dir}.json | pandoc -f markdown -t odt > {output_dir}.odt")
    os.system(f"python3 ../Sampler/tools/fmttable.py < {output_dir}.json | pandoc -f markdown -t odt > {output_dir}.odt")
    print("ODT has been genrated!\n")

