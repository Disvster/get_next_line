### 23/05

- gnl is working but I need to protect every memory allocation I do, which i'm not doing
- bonus is stable, base is dev
- NORMINETTE:
    - max functions in gnl.c and gnl_utils.c
    - max lines in gnl() but I need to wrap it bc of mallocs and frees
- strlcpy may be replaced by strjoin
- void funcs in gnl.c have to be changed to `char *` type for correct malloc protection and frees, and line saving
