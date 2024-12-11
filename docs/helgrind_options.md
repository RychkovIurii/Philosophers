valgrind --tool=helgrind ./philo

HELGRIND OPTIONS
       --free-is-write=no|yes [default: no]
           When enabled (not the default), Helgrind treats freeing of heap memory as if the memory was written immediately before the free. This exposes
           races where memory is referenced by one thread, and freed by another, but there is no observable synchronisation event to ensure that the
           reference happens before the free.

           This functionality is new in Valgrind 3.7.0, and is regarded as experimental. It is not enabled by default because its interaction with custom
           memory allocators is not well understood at present. User feedback is welcomed.

       --track-lockorders=no|yes [default: yes]
           When enabled (the default), Helgrind performs lock order consistency checking. For some buggy programs, the large number of lock order errors
           reported can become annoying, particularly if you're only interested in race errors. You may therefore find it helpful to disable lock order
           checking.

       --history-level=none|approx|full [default: full]
           --history-level=full (the default) causes Helgrind collects enough information about "old" accesses that it can produce two stack traces in a
           race report -- both the stack trace for the current access, and the trace for the older, conflicting access. To limit memory usage, "old"
           accesses stack traces are limited to a maximum of 8 entries, even if --num-callers value is bigger.

           Collecting such information is expensive in both speed and memory, particularly for programs that do many inter-thread synchronisation events
           (locks, unlocks, etc). Without such information, it is more difficult to track down the root causes of races. Nonetheless, you may not need it in
           situations where you just want to check for the presence or absence of races, for example, when doing regression testing of a previously
           race-free program.

           --history-level=none is the opposite extreme. It causes Helgrind not to collect any information about previous accesses. This can be dramatically
           faster than --history-level=full.

           --history-level=approx provides a compromise between these two extremes. It causes Helgrind to show a full trace for the later access, and
           approximate information regarding the earlier access. This approximate information consists of two stacks, and the earlier access is guaranteed
           to have occurred somewhere between program points denoted by the two stacks. This is not as useful as showing the exact stack for the previous
           access (as --history-level=full does), but it is better than nothing, and it is almost as fast as --history-level=none.

       --delta-stacktrace=no|yes [default: yes on linux amd64/x86]
           This flag only has any effect at --history-level=full.

           --delta-stacktrace configures the way Helgrind captures the stacktraces for the option --history-level=full. Such a stacktrace is typically
           needed each time a new piece of memory is read or written in a basic block of instructions.

           --delta-stacktrace=no causes Helgrind to compute a full history stacktrace from the unwind info each time a stacktrace is needed.

           --delta-stacktrace=yes indicates to Helgrind to derive a new stacktrace from the previous stacktrace, as long as there was no call instruction,
           no return instruction, or any other instruction changing the call stack since the previous stacktrace was captured. If no such instruction was
           executed, the new stacktrace can be derived from the previous stacktrace by just changing the top frame to the current program counter. This
           option can speed up Helgrind by 25% when using --history-level=full.
		--delta-stacktrace configures the way Helgrind captures the stacktraces for the option --history-level=full. Such a stacktrace is typically
           needed each time a new piece of memory is read or written in a basic block of instructions.

           --delta-stacktrace=no causes Helgrind to compute a full history stacktrace from the unwind info each time a stacktrace is needed.

           --delta-stacktrace=yes indicates to Helgrind to derive a new stacktrace from the previous stacktrace, as long as there was no call instruction,
           no return instruction, or any other instruction changing the call stack since the previous stacktrace was captured. If no such instruction was
           executed, the new stacktrace can be derived from the previous stacktrace by just changing the top frame to the current program counter. This
           option can speed up Helgrind by 25% when using --history-level=full.

           The following aspects have to be considered when using --delta-stacktrace=yes :

           •   In some cases (for example in a function prologue), the valgrind unwinder might not properly unwind the stack, due to some limitations and/or
               due to wrong unwind info. When using --delta-stacktrace=yes, the wrong stack trace captured in the function prologue will be kept till the
               next call or return.

           •   On the other hand, --delta-stacktrace=yes sometimes helps to obtain a correct stacktrace, for example when the unwind info allows a correct
               stacktrace to be done in the beginning of the sequence, but not later on in the instruction sequence.

           •   Determining which instructions are changing the callstack is partially based on platform dependent heuristics, which have to be
               tuned/validated specifically for the platform. Also, unwinding in a function prologue must be good enough to allow using
               --delta-stacktrace=yes. Currently, the option --delta-stacktrace=yes has been reasonably validated only on linux x86 32 bits and linux amd64
               64 bits. For more details about how to validate --delta-stacktrace=yes, see debug option --hg-sanity-flags and the function
               check_cached_rcec_ok in libhb_core.c.

       --conflict-cache-size=N [default: 1000000]
           This flag only has any effect at --history-level=full.

           Information about "old" conflicting accesses is stored in a cache of limited size, with LRU-style management. This is necessary because it isn't
           practical to store a stack trace for every single memory access made by the program. Historical information on not recently accessed locations is
           periodically discarded, to free up space in the cache.

           This option controls the size of the cache, in terms of the number of different memory addresses for which conflicting access information is
           stored. If you find that Helgrind is showing race errors with only one stack instead of the expected two stacks, try increasing this value.

           The minimum value is 10,000 and the maximum is 30,000,000 (thirty times the default value). Increasing the value by 1 increases Helgrind's memory
           requirement by very roughly 100 bytes, so the maximum value will easily eat up three extra gigabytes or so of memory.
		   --check-stack-refs=no|yes [default: yes]
           By default Helgrind checks all data memory accesses made by your program. This flag enables you to skip checking for accesses to thread stacks
           (local variables). This can improve performance, but comes at the cost of missing races on stack-allocated data.

       --ignore-thread-creation=<yes|no> [default: no]
           Controls whether all activities during thread creation should be ignored. By default enabled only on Solaris. Solaris provides higher throughput,
           parallelism and scalability than other operating systems, at the cost of more fine-grained locking activity. This means for example that when a
           thread is created under glibc, just one big lock is used for all thread setup. Solaris libc uses several fine-grained locks and the creator
           thread resumes its activities as soon as possible, leaving for example stack and TLS setup sequence to the created thread. This situation
           confuses Helgrind as it assumes there is some false ordering in place between creator and created thread; and therefore many types of race
           conditions in the application would not be reported. To prevent such false ordering, this command line option is set to yes by default on
           Solaris. All activity (loads, stores, client requests) is therefore ignored during:

           •   pthread_create() call in the creator thread

           •   thread creation phase (stack and TLS setup) in the created thread

           Also new memory allocated during thread creation is untracked, that is race reporting is suppressed there. DRD does the same thing implicitly.
           This is necessary because Solaris libc caches many objects and reuses them for different threads and that confuses Helgrind.