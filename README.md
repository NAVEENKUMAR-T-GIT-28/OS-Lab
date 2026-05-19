# OS Lab Programs — Complete Reference

---

## 1. Shell Script — Swap Two Numbers

### Aim
To write a shell script to swap two numbers.

### Algorithm
1. Start.
2. Read two numbers `a` and `b` from the user.
3. Print values before swap.
4. Store `a` in a temporary variable `temp`.
5. Assign `b` to `a`.
6. Assign `temp` to `b`.
7. Print the swapped values.
8. Stop.

### Code
```bash
#!/bin/bash
echo "Enter two numbers:"
read a b
echo "Before swap: a=$a  b=$b"
temp=$a
a=$b
b=$temp
echo "After swap:  a=$a  b=$b"
```

### Input
```
Enter two numbers:
10 20
```

### Output
```
Before swap: a=10  b=20
After swap:  a=20  b=10
```

---

## 2. Shell Script — Vowel or Not

### Aim
To write a shell script to check whether a given character is a vowel or not.

### Algorithm
1. Start.
2. Read a character from the user.
3. Check if the character matches any of: a, e, i, o, u (upper or lower case).
4. If match found — print "It is a Vowel".
5. Else — print "It is not a Vowel".
6. Stop.

### Code
```bash
#!/bin/bash
echo "Enter a character:"
read ch
case $ch in
  [aeiouAEIOU]) echo "$ch is a Vowel" ;;
  *) echo "$ch is not a Vowel" ;;
esac
```

### Input
```
Enter a character:
A
```

### Output
```
A is a Vowel
```

---

## 3. Process Management — fork()

### Aim
To demonstrate the creation of a child process using the `fork()` system call.

### Algorithm
1. Start.
2. Call `fork()` to create a child process. It returns a `pid`.
3. If `pid < 0` — fork failed, print error and exit.
4. If `pid == 0` — we are in the child process; print child PID.
5. If `pid > 0` — we are in the parent process; print parent PID and child PID.
6. Stop.

### Code
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else {
        printf("Parent Process: PID=%d, Child PID=%d\n", getpid(), pid);
    }
    return 0;
}
```

### Input
```
(No input required)
```

### Output
```
Parent Process: PID=1234, Child PID=1235
Child Process: PID=1235, Parent PID=1234
```

---

## 4. Process Management — wait()

### Aim
To demonstrate process synchronization between parent and child using `wait()`.

### Algorithm
1. Start.
2. Call `fork()` to create a child process.
3. In the child process — perform a task, then call `exit(0)`.
4. In the parent process — call `wait(&status)` to block until child finishes.
5. After `wait()` returns, extract and print exit status using `WEXITSTATUS(status)`.
6. Parent resumes and terminates.
7. Stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child (PID %d) is running...\n", getpid());
        sleep(2);
        printf("Child done.\n");
        exit(0);
    } else {
        int status;
        printf("Parent waiting for child %d...\n", pid);
        wait(&status);
        printf("Child exited with status: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### Input
```
(No input required)
```

### Output
```
Parent waiting for child 1235...
Child (PID 1235) is running...
Child done.
Child exited with status: 0
```

---

## 5. Process Management — exec() with ls

### Aim
To demonstrate replacing a process image using `execl()` to run the `ls -l` command.

### Algorithm
1. Start.
2. Call `fork()` to create a child process.
3. In the child process — call `execl("/bin/ls", "ls", "-l", NULL)`.
4. `execl()` replaces the child's memory with the `ls` program.
5. If `execl()` fails, print error and exit.
6. In the parent process — call `wait()` for child to finish.
7. Print child's exit status.
8. Stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child (PID %d) running ls -l:\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec failed");
        exit(1);
    } else {
        int status;
        wait(&status);
        printf("Parent: child exited with %d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

### Input
```
(No input required)
```

### Output
```
Child (PID 1235) running ls -l:
total 16
-rwxr-xr-x 1 user user 16728 Apr 16 01:00 a.out
-rw-r--r-- 1 user user  854  Apr 16 00:58 main.c
Parent: child exited with 0
```

---

## 6. Process Management — readdir()

### Aim
To list all files in the current directory using the `readdir()` system call.

### Algorithm
1. Start.
2. Call `opendir(".")` to open the current directory.
3. If `opendir` returns NULL — print error and exit.
4. Loop: call `readdir(dir)` repeatedly.
5. Each call returns a `dirent` struct containing `d_name` (filename).
6. Print each entry's name.
7. Loop until `readdir` returns NULL (end of directory).
8. Call `closedir()` to release the directory.
9. Stop.

### Code
```c
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
    struct dirent *entry;
    if (!d) {
        perror("opendir failed");
        return 1;
    }
    printf("Files in current directory:\n");
    while ((entry = readdir(d)) != NULL)
        printf("  %s\n", entry->d_name);
    closedir(d);
    return 0;
}
```

### Input
```
(No input required)
```

### Output
```
Files in current directory:
  .
  ..
  main.c
  a.out
```

---

## 7. CPU Scheduling — FCFS

### Aim
To implement the First Come First Serve (FCFS) CPU scheduling algorithm.

### Algorithm
1. Start.
2. Accept number of processes `n`.
3. For each process, accept its burst time.
4. Set WT[0] = 0 and TAT[0] = BT[0].
5. For each process i from 1 to n−1:
   - WT[i] = WT[i−1] + BT[i−1]
   - TAT[i] = WT[i] + BT[i]
6. Calculate Average WT = Total WT / n.
7. Calculate Average TAT = Total TAT / n.
8. Display the table and averages.
9. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20];
    float wtavg = 0, tatavg = 0;
    printf("Number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Burst time P%d: ", i);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;
    tat[0] = bt[0];
    tatavg = tat[0];
    for (int i = 1; i < n; i++) {
        wt[i]   = wt[i-1] + bt[i-1];
        tat[i]  = wt[i] + bt[i];
        wtavg  += wt[i];
        tatavg += tat[i];
    }
    printf("\nP\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i, bt[i], wt[i], tat[i]);
    printf("Average WT  = %.2f\n", wtavg / n);
    printf("Average TAT = %.2f\n", tatavg / n);
    return 0;
}
```

### Input
```
Number of processes: 3
Burst time P0: 24
Burst time P1: 3
Burst time P2: 3
```

### Output
```
P   BT   WT   TAT
P0  24    0    24
P1   3   24    27
P2   3   27    30
Average WT  = 17.00
Average TAT = 27.00
```

---

## 8. CPU Scheduling — SJF

### Aim
To implement the Shortest Job First (SJF) CPU scheduling algorithm.

### Algorithm
1. Start.
2. Accept number of processes and their burst times.
3. Sort all processes in ascending order of burst time.
4. Set WT[0] = 0 and TAT[0] = BT[0].
5. For each process i from 1 to n−1:
   - WT[i] = WT[i−1] + BT[i−1]
   - TAT[i] = WT[i] + BT[i]
6. Calculate Average WT and Average TAT.
7. Display process table and averages.
8. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int n, p[20], bt[20], wt[20], tat[20], temp;
    float wtavg = 0, tatavg = 0;
    printf("Number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
        printf("Burst P%d: ", i);
        scanf("%d", &bt[i]);
    }
    for (int i = 0; i < n; i++)
        for (int k = i+1; k < n; k++)
            if (bt[i] > bt[k]) {
                temp = bt[i]; bt[i] = bt[k]; bt[k] = temp;
                temp = p[i];  p[i]  = p[k];  p[k]  = temp;
            }
    wt[0] = 0; tat[0] = bt[0]; tatavg = tat[0];
    for (int i = 1; i < n; i++) {
        wt[i]   = wt[i-1] + bt[i-1];
        tat[i]  = tat[i-1] + bt[i];
        wtavg  += wt[i];
        tatavg += tat[i];
    }
    printf("\nP\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    printf("Average WT  = %.2f\n", wtavg / n);
    printf("Average TAT = %.2f\n", tatavg / n);
    return 0;
}
```

### Input
```
Number of processes: 4
Burst P0: 6
Burst P1: 8
Burst P2: 7
Burst P3: 3
```

### Output
```
P   BT   WT   TAT
P3   3    0     3
P0   6    3     9
P2   7    9    16
P1   8   16    24
Average WT  = 7.00
Average TAT = 13.00
```

---

## 9. CPU Scheduling — Round Robin

### Aim
To implement the Round Robin CPU scheduling algorithm.

### Algorithm
1. Start.
2. Accept number of processes, burst times, and time quantum `tq`.
3. Calculate total burst time `ttat` = sum of all burst times.
4. Initialise time counter `j = 0`.
5. Repeat until `j = ttat`:
   - For each process with remaining BT > 0:
     - If BT > tq: subtract tq from BT, add tq to j.
     - If BT ≤ tq: TAT = j + BT, WT = TAT − original BT, set BT = 0.
6. Calculate Average WT and Average TAT.
7. Display results.
8. Stop.

### Code
```c
#include <stdio.h>

struct proc { int pn, bt, wt, tat; } p[10];

int main() {
    int tq, n, b[10], ttat = 0, j = 0;
    float awt = 0, atat = 0;
    printf("No of processes: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("PID & Burst time: ");
        scanf("%d %d", &p[i].pn, &p[i].bt);
        b[i] = p[i].bt;
        ttat += p[i].bt;
    }
    printf("Time quantum: ");
    scanf("%d", &tq);
    while (j < ttat)
        for (int i = 1; i <= n; i++)
            if (p[i].bt > 0) {
                if (p[i].bt > tq) { p[i].bt -= tq; j += tq; }
                else {
                    j += p[i].bt;
                    p[i].tat = j;
                    p[i].wt  = p[i].tat - b[i];
                    atat += p[i].tat;
                    awt  += p[i].wt;
                    p[i].bt = 0;
                }
            }
    printf("\nP\tBT\tWT\tTAT\n");
    for (int i = 1; i <= n; i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pn, b[i], p[i].wt, p[i].tat);
    printf("Average WT  = %.2f\n", awt / n);
    printf("Average TAT = %.2f\n", atat / n);
    return 0;
}
```

### Input
```
No of processes: 3
PID & Burst time: 1 24
PID & Burst time: 2 3
PID & Burst time: 3 3
Time quantum: 4
```

### Output
```
P   BT   WT   TAT
1   24    6    30
2    3    4     7
3    3    7    10
Average WT  = 5.67
Average TAT = 15.67
```

---

## 10. CPU Scheduling — Priority

### Aim
To implement the Priority CPU scheduling algorithm.

### Algorithm
1. Start.
2. Accept number of processes, burst times, and priority values.
3. Sort processes in ascending order of priority (lower number = higher priority).
4. If two processes have the same priority, apply FCFS among them.
5. Set WT[0] = 0 and TAT[0] = BT[0].
6. For each process i from 1 to n−1:
   - WT[i] = WT[i−1] + BT[i−1]
   - TAT[i] = WT[i] + BT[i]
7. Calculate Average WT and Average TAT.
8. Display table with priorities and averages.
9. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int n, p[20], bt[20], pri[20], wt[20], tat[20], temp;
    float wtavg = 0, tatavg = 0;
    printf("Number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
        printf("Burst & Priority P%d: ", i);
        scanf("%d %d", &bt[i], &pri[i]);
    }
    for (int i = 0; i < n; i++)
        for (int k = i+1; k < n; k++)
            if (pri[i] > pri[k]) {
                temp = p[i];   p[i]   = p[k];   p[k]   = temp;
                temp = bt[i];  bt[i]  = bt[k];  bt[k]  = temp;
                temp = pri[i]; pri[i] = pri[k]; pri[k] = temp;
            }
    wt[0] = 0; tat[0] = bt[0]; tatavg = tat[0];
    for (int i = 1; i < n; i++) {
        wt[i]   = wt[i-1] + bt[i-1];
        tat[i]  = tat[i-1] + bt[i];
        wtavg  += wt[i];
        tatavg += tat[i];
    }
    printf("\nP\tPRI\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], pri[i], bt[i], wt[i], tat[i]);
    printf("Average WT  = %.2f\n", wtavg / n);
    printf("Average TAT = %.2f\n", tatavg / n);
    return 0;
}
```

### Input
```
Number of processes: 5
Burst & Priority P0: 10 3
Burst & Priority P1: 1 1
Burst & Priority P2: 2 4
Burst & Priority P3: 1 5
Burst & Priority P4: 5 2
```

### Output
```
P    PRI   BT   WT   TAT
P1    1     1    0     1
P4    2     5    1     6
P0    3    10    6    16
P2    4     2   16    18
P3    5     1   18    19
Average WT  = 8.20
Average TAT = 12.00
```

---

## 11. Memory Allocation — First Fit

### Aim
To implement the First Fit memory allocation strategy.

### Algorithm
1. Start.
2. Input number of memory blocks and their sizes.
3. Input number of processes and their sizes.
4. For each process i, scan blocks from the beginning:
   - Find the first free block where block_size ≥ process_size.
   - Allocate that block and mark it as used.
5. If no block found, process remains unallocated.
6. Display the allocation table.
7. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int bsize[10], psize[10], bno, pno, flags[10], alloc[10];
    for (int i = 0; i < 10; i++) { flags[i] = 0; alloc[i] = -1; }
    printf("No of blocks: "); scanf("%d", &bno);
    for (int i = 0; i < bno; i++) { printf("Block %d size: ", i+1); scanf("%d", &bsize[i]); }
    printf("No of processes: "); scanf("%d", &pno);
    for (int i = 0; i < pno; i++) { printf("Process %d size: ", i+1); scanf("%d", &psize[i]); }
    for (int i = 0; i < pno; i++)
        for (int j = 0; j < bno; j++)
            if (!flags[j] && bsize[j] >= psize[i]) {
                alloc[j] = i; flags[j] = 1; break;
            }
    printf("\nBlock\tSize\tProcess\tPSize\n");
    for (int i = 0; i < bno; i++) {
        printf("%d\t%d\t", i+1, bsize[i]);
        if (flags[i]) printf("P%d\t%d\n", alloc[i]+1, psize[alloc[i]]);
        else printf("Not allocated\n");
    }
    return 0;
}
```

### Input
```
No of blocks: 3
Block 1 size: 5
Block 2 size: 2
Block 3 size: 7
No of processes: 2
Process 1 size: 1
Process 2 size: 4
```

### Output
```
Block  Size  Process  PSize
1       5    P1        1
2       2    Not allocated
3       7    P2        4
```

---

## 12. Memory Allocation — Best Fit

### Aim
To implement the Best Fit memory allocation strategy.

### Algorithm
1. Start.
2. Input memory blocks and process sizes.
3. For each process i, scan all free blocks:
   - Find the block with the smallest (block_size − process_size) ≥ 0.
   - Allocate that block (minimum leftover fragment).
4. If no suitable block found, process is unallocated.
5. Display allocation table with fragment sizes.
6. Stop.

### Code
```c
#include <stdio.h>
#define MAX 25

int main() {
    int b[MAX], f[MAX], bf[MAX]={0}, ff[MAX]={0}, frag[MAX];
    int nb, nf, lowest;
    printf("No of blocks: "); scanf("%d", &nb);
    for (int i = 1; i <= nb; i++) { printf("Block %d: ", i); scanf("%d", &b[i]); }
    printf("No of files: "); scanf("%d", &nf);
    for (int i = 1; i <= nf; i++) { printf("File %d: ", i); scanf("%d", &f[i]); }
    for (int i = 1; i <= nf; i++) {
        lowest = 10000;
        for (int j = 1; j <= nb; j++) {
            if (!bf[j]) {
                int temp = b[j] - f[i];
                if (temp >= 0 && temp < lowest) { ff[i] = j; lowest = temp; }
            }
        }
        frag[i] = lowest; bf[ff[i]] = 1;
    }
    printf("\nFile\tFSize\tBlock\tBSize\tFrag\n");
    for (int i = 1; i <= nf && ff[i]; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", i, f[i], ff[i], b[ff[i]], frag[i]);
    return 0;
}
```

### Input
```
No of blocks: 3
Block 1: 5
Block 2: 2
Block 3: 7
No of files: 2
File 1: 1
File 2: 4
```

### Output
```
File  FSize  Block  BSize  Frag
1       1      2      2      1
2       4      1      5      1
```

---

## 13. Deadlock Avoidance — Banker's Algorithm

### Aim
To implement the Banker's Algorithm for deadlock avoidance.

### Algorithm
1. Start.
2. Input number of processes and resource types.
3. Input Allocation matrix, Max matrix, and Available vector.
4. Calculate Need matrix: Need[i][j] = Max[i][j] − Alloc[i][j].
5. Initialise all processes as unfinished.
6. Repeat:
   - Find an unfinished process i where Need[i] ≤ Available.
   - If found: add Alloc[i] to Available, mark i finished, add to safe sequence.
   - If not found and processes remain: print UNSAFE STATE and stop.
7. If all processes finish — print SAFE STATE and safe sequence.
8. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int pn, rn, alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0}, safe[10], count = 0;
    printf("Processes: "); scanf("%d", &pn);
    printf("Resources: "); scanf("%d", &rn);
    printf("Allocation matrix:\n");
    for (int i = 0; i < pn; i++)
        for (int j = 0; j < rn; j++) scanf("%d", &alloc[i][j]);
    printf("Max matrix:\n");
    for (int i = 0; i < pn; i++)
        for (int j = 0; j < rn; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    printf("Available: ");
    for (int i = 0; i < rn; i++) scanf("%d", &avail[i]);
    int s = 0;
    while (count < pn) {
        int found = 0;
        for (int i = 0; i < pn; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < rn; j++)
                    if (need[i][j] > avail[j]) { ok = 0; break; }
                if (ok) {
                    for (int j = 0; j < rn; j++) avail[j] += alloc[i][j];
                    finish[i] = 1; safe[s++] = i; count++; found = 1;
                }
            }
        }
        if (!found) { printf("UNSAFE STATE — Deadlock possible!\n"); return 0; }
    }
    printf("SAFE STATE. Safe sequence: ");
    for (int i = 0; i < pn; i++) printf("P%d ", safe[i]);
    printf("\n");
    return 0;
}
```

### Input
```
Processes: 5
Resources: 3
Allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Max matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Available: 3 3 2
```

### Output
```
SAFE STATE. Safe sequence: P1 P3 P4 P0 P2
```

---

## 14. Deadlock Detection Algorithm

### Aim
To implement a deadlock detection algorithm to check whether the system is in a safe or unsafe state.

### Algorithm
1. Start.
2. Input number of processes and resource types.
3. Input Claim matrix and Allocated matrix.
4. Calculate Need matrix: Need[i][j] = Claim[i][j] − Alloc[i][j]. Display it.
5. Input Available resource vector.
6. For each process, check if Need[i] ≤ Available for all resources.
7. If yes for all processes → Safe State. Else → Unsafe State.
8. Print result.
9. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int m, n, cl[10][10], al[10][10], av[10], ne[10][10], flag = 1;
    printf("Processes, Resources: "); scanf("%d %d", &m, &n);
    printf("Claim matrix:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) scanf("%d", &cl[i][j]);
    printf("Allocated matrix:\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) scanf("%d", &al[i][j]);
    printf("Need matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ne[i][j] = cl[i][j] - al[i][j];
            printf("%d ", ne[i][j]);
        }
        printf("\n");
    }
    printf("Available: ");
    for (int i = 0; i < n; i++) scanf("%d", &av[i]);
    for (int i = 0; i < m && flag; i++)
        for (int j = 0; j < n; j++)
            if (av[j] < ne[i][j]) { flag = 0; break; }
    printf(flag ? "Safe State\n" : "Unsafe State\n");
    return 0;
}
```

### Input
```
Processes, Resources: 4 3
Claim matrix:
3 2 2
6 1 3
3 1 4
4 2 2
Allocated matrix:
1 0 0
5 1 1
2 1 1
0 0 2
Available: 1 1 2
```

### Output
```
Need matrix:
2 2 2
1 0 2
1 0 3
4 2 0
Safe State
```

---

## 15. Semaphores — Producer-Consumer Problem

### Aim
To implement the Producer-Consumer problem using semaphores to ensure mutual exclusion and avoid buffer overflow/underflow.

### Algorithm
1. Start. Initialise: mutex=1, full=0, empty=3 (buffer size).
2. **Producer process:**
   - wait(mutex): decrement mutex.
   - wait(empty): decrement empty.
   - Add item to buffer, increment item counter x.
   - signal(mutex): increment mutex.
   - signal(full): increment full.
3. **Consumer process:**
   - wait(mutex): decrement mutex.
   - wait(full): decrement full.
   - Remove item from buffer, decrement x.
   - signal(mutex): increment mutex.
   - signal(empty): increment empty.
4. Producer cannot produce when buffer is full (empty == 0).
5. Consumer cannot consume when buffer is empty (full == 0).
6. Print buffer status after each operation.
7. Stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 3, x = 0;

void producer() {
    --mutex; ++full; --empty; x++;
    printf("Producer produces item %d\n", x);
    ++mutex;
}

void consumer() {
    --mutex; --full; ++empty;
    printf("Consumer consumes item %d\n", x);
    x--; ++mutex;
}

int main() {
    int n;
    printf("1=Producer  2=Consumer  3=Exit\n");
    for (;;) {
        printf("Choice: "); scanf("%d", &n);
        if      (n == 1) { if (mutex==1 && empty!=0) producer(); else printf("Buffer full!\n"); }
        else if (n == 2) { if (mutex==1 && full!=0)  consumer(); else printf("Buffer empty!\n"); }
        else break;
    }
    return 0;
}
```

### Input
```
1=Producer  2=Consumer  3=Exit
Choice: 1
Choice: 1
Choice: 2
Choice: 2
Choice: 2
Choice: 3
```

### Output
```
Producer produces item 1
Producer produces item 2
Consumer consumes item 2
Consumer consumes item 1
Buffer empty!
```

---

## 16. Multithreading using Pthreads

### Aim
To implement multithreading in C using the POSIX `pthread` library.

### Algorithm
1. Start.
2. Define a thread function that accepts a `void*` argument.
3. In the thread function, perform the desired task and return NULL.
4. In `main()`, declare thread identifiers of type `pthread_t`.
5. Call `pthread_create()` for each thread, passing the function and argument.
6. Call `pthread_join()` for each thread to wait until it finishes.
7. Continue with main program after all threads complete.
8. Stop.
   
   Compile: `gcc thread.c -lpthread -o thread`

### Code
```c
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d is running\n", id);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    pthread_create(&t1, NULL, thread_func, &id1);
    pthread_create(&t2, NULL, thread_func, &id2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Both threads finished.\n");
    return 0;
}
```

### Input
```
(No input required)
```

### Output
```
Thread 1 is running
Thread 2 is running
Both threads finished.
```

---

## 17. Page Replacement — FIFO

### Aim
To implement the First In First Out (FIFO) page replacement algorithm.

### Algorithm
1. Start.
2. Input page reference string and number of frames.
3. Initialise all frames to -1. Set pointer j=0, fault count=0.
4. For each page reference:
   - Check if page is already in a frame (page hit).
   - If hit — do nothing.
   - If miss (page fault): place page in frame[j], j=(j+1)%frames, increment fault count.
5. Print frame state after each reference.
6. Print total page faults.
7. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int n, no, a[20], frame[20], count=0, j=0, avail, k;
    printf("No of pages: "); scanf("%d", &n);
    printf("Page reference string: ");
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    printf("No of frames: "); scanf("%d", &no);
    for (int i = 0; i < no; i++) frame[i] = -1;
    printf("\nRef\tFrames\n");
    for (int i = 1; i <= n; i++) {
        printf("%d\t", a[i]);
        avail = 0;
        for (k = 0; k < no; k++) if (frame[k] == a[i]) avail = 1;
        if (!avail) {
            frame[j] = a[i]; j = (j+1) % no; count++;
            for (k = 0; k < no; k++) printf("%d ", frame[k]);
        }
        printf("\n");
    }
    printf("Page faults: %d\n", count);
    return 0;
}
```

### Input
```
No of pages: 10
Page reference string: 7 0 1 2 0 3 0 4 2 3
No of frames: 3
```

### Output
```
Ref   Frames
7     7 -1 -1
0     7  0 -1
1     7  0  1
2     2  0  1
0
3     2  3  1
0     2  3  0
4     4  3  0
2     4  2  0
3     4  2  3
Page faults: 9
```

---

## 18. Page Replacement — LRU

### Aim
To implement the Least Recently Used (LRU) page replacement algorithm.

### Algorithm
1. Start.
2. Input page reference string and number of frames.
3. Initialise all frames to 999 (empty).
4. For each page reference:
   - Search if page exists in frames.
   - If found (hit): move it to the front (most recently used).
   - If not found (fault): increment fault count, shift all frames right, insert new page at front.
5. Print frame state and "Fault" label for misses.
6. Print total page faults.
7. Stop.

### Code
```c
#include <stdio.h>

int main() {
    int n, f, q[20], p[20], pgf=0, st, t, cnt, j;
    printf("No of ref strings: "); scanf("%d", &n);
    printf("No of frames: "); scanf("%d", &f);
    printf("Strings: ");
    for (int i = 0; i < n; i++) scanf("%d", &q[i]);
    for (int i = 0; i < f; i++) p[i] = 999;
    for (int i = 0; i < n; i++) {
        st = 0;
        for (j = 0; j < f; j++)
            if (p[j] == q[i]) { st = 1; t = p[j]; cnt = j; }
        if (!st) {
            printf("Fault  "); pgf++;
            for (j = f; j > 0; j--) p[j] = p[j-1];
            p[0] = q[i];
        } else {
            for (j = cnt; j > 0; j--) p[j] = p[j-1];
            p[0] = t;
        }
        for (j = 0; j < f; j++) printf("%d ", p[j]);
        printf("\n");
    }
    printf("Total page faults: %d\n", pgf);
    return 0;
}
```

### Input
```
No of ref strings: 10
No of frames: 3
Strings: 7 0 1 2 0 3 0 4 2 3
```

### Output
```
Fault  7 999 999
Fault  0 7 999
Fault  1 0 7
Fault  2 1 0
0 2 1
Fault  3 0 2
0 3 2
Fault  4 0 3
Fault  2 4 0
Fault  3 2 4
Total page faults: 8
```

---

## 19. File Allocation — Sequential (Contiguous)

### Aim
To implement the Sequential (Contiguous) file allocation strategy.

### Algorithm
1. Start.
2. Initialise all 50 disk blocks as free (0).
3. Input starting block number and file length.
4. For each block from start to start+length:
   - If free — allocate (mark as 1) and print.
   - If already allocated — print error and stop.
5. If all blocks allocated successfully — print "File allocated to disk".
6. Ask user if they want to allocate another file.
7. If yes — repeat from step 3. Else stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>

int f[50];

int main() {
    int st, len, c;
    for (int i = 0; i < 50; i++) f[i] = 0;
    again:
    printf("Starting block & length: "); scanf("%d %d", &st, &len);
    int j;
    for (j = st; j < st+len; j++) {
        if (f[j] == 0) { f[j] = 1; printf("%d -> %d\n", j, f[j]); }
        else { printf("Block %d already allocated\n", j); break; }
    }
    if (j == st+len) printf("File allocated to disk\n");
    printf("More files? (1=yes 0=no): "); scanf("%d", &c);
    if (c == 1) goto again;
    return 0;
}
```

### Input
```
Starting block & length: 4 5
More files? (1=yes 0=no): 0
```

### Output
```
4 -> 1
5 -> 1
6 -> 1
7 -> 1
8 -> 1
File allocated to disk
```

---

## 20. File Allocation — Indexed

### Aim
To implement the Indexed file allocation strategy.

### Algorithm
1. Start.
2. Initialise all disk blocks as free.
3. Input an index block number. If already used — re-input.
4. Mark index block as allocated.
5. Input number of data blocks and their block numbers.
6. Check each data block — if any is already allocated, print error.
7. Allocate all data blocks and mark as used.
8. Print index block → each data block mapping.
9. Ask if more files — if yes repeat, else stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>

int f[50], inde[50];

int main() {
    int p, n, c;
    for (int i = 0; i < 50; i++) f[i] = 0;
    again:
    printf("Index block: "); scanf("%d", &p);
    if (f[p]) { printf("Block already allocated\n"); goto again; }
    f[p] = 1;
    printf("No of files on index: "); scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &inde[i]);
    for (int i = 0; i < n; i++)
        if (f[inde[i]]) { printf("Block %d already allocated\n", inde[i]); goto again; }
    for (int j = 0; j < n; j++) f[inde[j]] = 1;
    printf("Allocated. File indexed:\n");
    for (int k = 0; k < n; k++) printf("%d -> %d : %d\n", p, inde[k], f[inde[k]]);
    printf("More? (1=yes 0=no): "); scanf("%d", &c);
    if (c == 1) goto again;
    return 0;
}
```

### Input
```
Index block: 9
No of files on index: 3
1 2 3
More? (1=yes 0=no): 0
```

### Output
```
Allocated. File indexed:
9 -> 1 : 1
9 -> 2 : 1
9 -> 3 : 1
```

---

## 21. File Allocation — Linked

### Aim
To implement the Linked file allocation strategy.

### Algorithm
1. Start.
2. Initialise all disk blocks as free.
3. Input count of already-allocated blocks and mark them as used.
4. Input starting block and file length.
5. Starting from the given block, allocate blocks sequentially:
   - If block is free — allocate it and link to next block.
   - If block is already used — skip it and extend length by 1 to compensate.
6. Each block holds a pointer to the next (linked list structure).
7. Ask if more files — if yes repeat, else stop.

### Code
```c
#include <stdio.h>
#include <stdlib.h>

int f[50];

int main() {
    int p, a, st, len, c;
    for (int i = 0; i < 50; i++) f[i] = 0;
    printf("Already allocated block count: "); scanf("%d", &p);
    printf("Enter those block numbers: ");
    for (int i = 0; i < p; i++) { scanf("%d", &a); f[a] = 1; }
    again:
    printf("Starting block & length: "); scanf("%d %d", &st, &len);
    int k = len;
    for (int j = st; j < k+st; j++) {
        if (f[j] == 0) { f[j] = 1; printf("%d -> %d\n", j, f[j]); }
        else { printf("%d -> already allocated\n", j); k++; }
    }
    printf("More files? (1=yes 0=no): "); scanf("%d", &c);
    if (c == 1) goto again;
    return 0;
}
```

### Input
```
Already allocated block count: 3
Enter those block numbers: 4 7 9
Starting block & length: 3 5
More files? (1=yes 0=no): 0
```

### Output
```
3 -> 1
4 -> already allocated
5 -> 1
6 -> 1
7 -> already allocated
8 -> 1
9 -> already allocated
10 -> 1
11 -> 1
```

---

## 22. Basic UNIX Commands

### Aim
To study and execute basic UNIX commands.

### Algorithm
1. Start the terminal / login to the system.
2. Use `date` to display the current date and time.
3. Use `cal` to display the calendar.
4. Use `mkdir`, `cd`, `ls`, `rmdir` for directory operations.
5. Use `cat`, `cp`, `mv`, `rm` for file operations.
6. Use `head`, `tail`, `wc`, `sort` for text processing.
7. Use `who`, `whoami` to display user information.
8. Use `echo` and pipes (`|`) for output and chaining commands.
9. Use `chmod` to change file permissions.
10. Stop.

### Commands with Examples

```bash
# Date and time
date                  # Full date and time
date +%m              # Current month number
date +%h              # Month name
date +%d              # Day
date +%y              # Year (2-digit)
date +%H              # Hour
date +%M              # Minute
date +%S              # Second

# Calendar
cal                   # Current month
cal 2025              # Full year
cal 8 2025            # August 2025

# Directory operations
mkdir student         # Create directory
cd student            # Enter directory
cd ..                 # Go up one level
pwd                   # Print working directory
rmdir student         # Delete empty directory

# File operations
cat > file1           # Create file (Ctrl+D to save)
cat file1             # View file contents
cp file1 file2        # Copy file
mv file2 file3        # Move / rename file
rm file3              # Delete file

# Text utilities
head -5 file1         # First 5 lines
tail -5 file1         # Last 5 lines
wc file1              # Lines, words, characters
sort file1            # Sort contents
cut -c3 file1         # Cut 3rd column character

# Users
who                   # All logged-in users
whoami                # Current user

# Permissions
chmod u+x file1       # Add execute for owner
ls -l file1           # View permissions

# Pipes and chaining
echo "Hello UNIX"     # Print message
who | wc -l           # Count logged-in users
cat file1 | sort      # Sort file output
```

### Input / Output Examples

```
$ date
Thu Feb 12 01:22:34 IST 2009

$ whoami
student

$ mkdir test
$ cd test
$ cat > hello
Hello World
(Ctrl+D)
$ cat hello
Hello World

$ wc hello
1 2 12 hello

$ who | wc -l
5
```

### Result
Thus the basic UNIX commands were studied and executed successfully.

---

*End of OS Lab Programs*
