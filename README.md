# TEST: sigaction_oldact
The project shows how `oldact` works as the third argument of the system call `sigaction()` with a simple debugging. It is the `struct sigaction` that stores the previous action.

## Manual
![image](https://github.com/user-attachments/assets/3e021068-c965-4843-82cc-ffa11a9d86b3)

Link: https://man7.org/linux/man-pages/man2/sigaction.2.html

## Progress
1. Build the project, generating GDB debug information.

```
$ gcc -g -o TEST main.c
```

3. Open the program with GDB.

```
$ gdb TEST
```

3. Disassemble the main function.

```
(gdb) disas main
```

![image](https://github.com/user-attachments/assets/693518ad-1aee-4d29-9b37-643be635e6c6)

4. Check `call` instructions for `print_handler` function. You can find four calls in the example program.

![image](https://github.com/user-attachments/assets/54600991-386e-4564-8d7e-96e47760bee3)

5. Set breakpoints either at four `call ADDR <print_handler>`, or at `print_handler` once.

##### Option A
If you'd like to set a breakpoint at <+319>, type this:
```
(gdb) b *main+319
```

![image](https://github.com/user-attachments/assets/ad9d8de4-9860-4207-8c6c-739c9f2f3ec7)

##### Option B
If you'd like to set a breakpoint at <print_handler>, type this:
```
(gdb) b print_handler
```

![image](https://github.com/user-attachments/assets/a6ea5ac9-b024-4538-be57-d5ba051f571b)

6. Run the program.

```
(gdb) r
```

![image](https://github.com/user-attachments/assets/2a05a3d7-7020-40f2-9d6f-75a292e79ca0)

7. At every breakpoint, check the `oldact` variable. In the example, you can track it with `sold`.

##### Option A
To show `sold.sa_handler` in the main function, `print sold`.

```
(gdb) p sold
```

![image](https://github.com/user-attachments/assets/ee35c4ad-0ef1-4a51-b9f4-8ef905d13261)

##### Option B
To show `handler` of the second `print_handler` argument, `print handler`.

```
(gdb) p handler
```

![image](https://github.com/user-attachments/assets/478d9ae7-a9c2-4ec7-b104-ebe752c99f0d)

## Result
1. `sigaction(SIGALRM, NULL, &sold);` does not store any `sigaction` to `sold.sa_handler`.
![image](https://github.com/user-attachments/assets/7ebb8a3c-89b0-4555-b6e7-95eec8539645)

2. `sigaction(SIGALRM, &sa, &sold);` does not store any `sigaction` to `sold.sa_handler`, either.
![image](https://github.com/user-attachments/assets/6f8215cb-739b-4808-bc88-4feaa940be65)

3. `sigaction(SIGALRM, &sb, &sold);` stores `printA` to `sold.sa_handler`.
![image](https://github.com/user-attachments/assets/ff92e4a9-341a-4f6d-ae2d-95510e57640b)

4. `sigaction(SIGALRM, &sc, &sold);` stores `printB` to `sold.sa_handler`.
![image](https://github.com/user-attachments/assets/b5062267-76cb-4a63-92a9-1db9571426c8)

## Conclusion
In `sigaction()`, the `oldact` argument stores the previous `sigaction` when it is replaced by the new `sigaction`. It is the second argument of the function, `act`.

