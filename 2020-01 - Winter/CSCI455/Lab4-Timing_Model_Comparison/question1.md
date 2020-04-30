Summary
  : Lab 4 consists of a series of tests to measure the timing of a single send/recv communication using the ping-pong method. Based on the tests, you can estimate the `t_startup` and `t_data` with the least square regression method.


# Part 1: Estimating Communication Latency of MPI Send/Recv


![Console screenshot (1/3) of `mpi_latency` running with 96 compute nodes](assets/make-run1-cluster-1-horizontal.png)

![Console screenshot (1/3) of `mpi_latency` running with 96 compute nodes](assets/make-run1-cluster-2-horizontal.png){ width=90% }

![Console screenshot (1/3) of `mpi_latency` running with 96 compute nodes. Resulting estimations are `t_startup`=2.4 usec and `t_data`=0.0 usec.](assets/make-run1-cluster-3.png){ width=90% }
