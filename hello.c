#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/slab.h>


MODULE_LICENSE("GPL");

// work queue
static struct workqueue_struct *my_wq;
 
typedef struct {
  struct work_struct my_work;
  int    x;
} my_work_t;
 
my_work_t *work, *work2;
 
 
static void my_wq_function( struct work_struct *work)
{
  my_work_t *my_work = (my_work_t *)work;
 
  printk( "my_work.x %d\n", my_work->x );
 
  kfree( (void *)work );
 
  return;
}




char my_tasklet_data[]="my_tasklet_function was called";

void my_tasklet_function( unsigned long data )
{
  printk( "%s\n", (char *)data );
  return;
}

DECLARE_TASKLET( my_tasklet, my_tasklet_function, 
         (unsigned long) &my_tasklet_data );

int hello_init(void)
{
    pr_alert("Hello World :)\n");
    //tasklet_schedule( &my_tasklet );

    int ret;
     
      my_wq = create_workqueue("my_queue");
      if (my_wq) {
     
        /* Queue some work (item 1) */
        work = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
        if (work) {
     
          INIT_WORK( (struct work_struct *)work, my_wq_function );
     
          work->x = 1;
     
          ret = queue_work( my_wq, (struct work_struct *)work );
     
        }
     
        /* Queue some additional work (item 2) */
        work2 = (my_work_t *)kmalloc(sizeof(my_work_t), GFP_KERNEL);
        if (work2) {
     
          INIT_WORK( (struct work_struct *)work2, my_wq_function );
     
          work2->x = 2;
     
          ret = queue_work( my_wq, (struct work_struct *)work2 );
     
        }
     
      }
     
    return 0;
}
void hello_exit(void)
{
    pr_alert("Goodbye World!\n");
    //tasklet_kill( &my_tasklet );

    flush_workqueue( my_wq );
    
     destroy_workqueue( my_wq );

    return;
}
module_init(hello_init);
module_exit(hello_exit);

