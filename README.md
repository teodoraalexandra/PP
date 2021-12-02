# PP

## How to run?

```console
sh do_it.sh param1 param2 param3 param4
```

1. number of proceses
2. length of the data (bytes)
3. number of trials
4. file name

## Algorithms for broadcast

* simple
* chain
* binary
* binomial

## Execution time

**Simple (50 trials)**
In this algorithm, the parent process (0) sends data to all its children. All children receive the message from process 0.

| Processes         | 1             | 4             | 16            | 64            | 256           |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data: 8 bytes     | 165324736     | 204673769     | 448434144     | 140125524     | 141286892     |          
| Data: 1 kb        | 179487600     | 212389727     | 457343345     | 145367019     | 141573174     |
| Data: 64 kb       | 180654502     | 209269577     | 463141398     | 126625701     | 132715058     |
| Data: 512 kb      | 178553532     | 208681719     | 470616096     | 140971326     | 140706331     |
| Data: 1 Mb        | 176297993     | 205180695     | 465323078     | 141765439     | 142048781     |

**Chain (50 trials)**
In this algorithm, the parent process (first) sends data only to its first child. Last process (n) receives data from proces n-1 and sends nothing. Other processes (not first nor last) sends data to next process and receives data from previous process.

| Processes         | 1             | 4             | 16            | 64            | 256           |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data: 8 bytes     | 175442327     | 201635912     | 442238182     | 159703039     | 136404840     |          
| Data: 1 kb        | 181996983     | 208095231     | 467114363     | 144081372     | 140303190     |
| Data: 64 kb       | 174712531     | 207326056     | 461897743     | 139914048     | 144834330     |
| Data: 512 kb      | 178222695     | 213075128     | 443299488     | 131970529     | 141280852     |
| Data: 1 Mb        | 179340602     | 208552319     | 461695163     | 139072808     | 141329465     |

**Binary (50 trials)**
In this algorithm, the parent process sends data to 2 child process. The process that is not leaf in the binary tree, receives data from parent and sends data to next 2 childs. Leaf processes do not send data, they only receive from parent.

| Processes         | 1             | 3             | 15            | 63            | 255           |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data: 8 bytes     | 176732248     | 190479375     | 428970040     | 139615688     | 136904086     |          
| Data: 1 kb        | 191324480     | 186212436     | 435848794     | 129469536     | 131567136     |
| Data: 64 kb       | 168910094     | 192484191     | 423422591     | 149924051     | 142399279     |
| Data: 512 kb      | 177172998     | 194562918     | 432224650     | 144551208     | 142964668     |
| Data: 1 Mb        | 178267361     | 192951688     | 444934022     | 142708104     | 156350535     |


**Binomial (50 trials)**
In this algorithm, each process id can be seen as a binary number, and we will compute the source and destination using bitwise operations. Everytime a new process is created, it will become parent in the next generation. 

| Processes         | 1             | 4             | 16            | 64            | 256           |
| ----------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data: 8 bytes     | 176625785     | 210752981     | 451765470     | 140822245     | 143672003     |          
| Data: 1 kb        | 182476504     | 206374966     | 466472949     | 143003978     | 141564087     |
| Data: 64 kb       | 180280868     | 211074611     | 463993604     | 141338914     | 144224685     |
| Data: 512 kb      | 180524892     | 209013157     | 450099673     | 137441736     | 141685388     |
| Data: 1 Mb        | 175434870     | 202857436     | 471924466     | 140974574     | 141040401     |
