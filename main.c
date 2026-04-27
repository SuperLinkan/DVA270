#include "Declarationer_&_initieringar.h"
#include "list.c"



int main(void)
{
    uarte_init();
    button_LED_init();
    systick_init();
    RTC_init();
    List stack_head = create_empty_list();

    List stack_tail = create_empty_list();

    List kö_head = create_empty_list();

    List kö_tail = create_empty_list();
    clear();
    
    

    void front_and_peak(int uneven_counter,int even_counter, List kö_head, List stack_head)
    {
        new_line();
        new_line();
        /*if (search_uneven_element(tail) == 1)
        {
            send_int(search_uneven_element(tail));
            //send_int(get_first_uneven_element(head));
            new_line();
        }
        
        else if (search_uneven_element(tail) == 0)
        {
            send_int(search_uneven_element(tail));
            //send_int(get_first_element(head));
            new_line();
        }*/
        if (uneven_counter > 0)
        {
            send_int(get_first_element(kö_head));
            new_line();
        }
        if (even_counter > 0)
        {
            send_int(get_last_element(stack_head));
        }
        new_line();

        new_line();
        //print_list(head);
    }

    while(1)
    { 
        //srand(nrfx_rtc_counter_get(&rtc_instance));
        int loop = 1;
        int ran_num;
        int uneven_elements = 0;
        int even_elements = 0;
        while (loop = 1)
        {
            nrfx_systick_delay_ms(50);
            if (nrf_gpio_pin_read(BUTTON1) == 0)
            {

                ran_num = rand() %10+1;
                nrfx_systick_delay_ms(1000);
                new_line();
        
                if (ran_num %2 == 0)
                {
                add_first(&stack_head, &stack_tail, ran_num);
                print_list(stack_head);
                even_elements += 1;
                }
                
                else if (ran_num %2 == 1)
                {
                add_last(&kö_head, &kö_tail, ran_num);
                print_list(kö_head);
                uneven_elements += 1;
                }
                front_and_peak(uneven_elements, even_elements, kö_head, stack_head);
                
            }
            else if (nrf_gpio_pin_read(BUTTON2) == 0)
            {
            //front_and_peak();
                if (uneven_elements > 0)
                {
                //send_int(get_first_uneven_element(kö_head));
                remove_element(&kö_head, &kö_tail, get_first_element(kö_head));
                uneven_elements -= 1;
                }
                
                new_line();
                //print_list(head);
                //front_and_peak(uneven_elements, even_elements);
                front_and_peak(uneven_elements, even_elements, kö_head, stack_head);

                nrfx_systick_delay_ms(1000);
            }
            else if (nrf_gpio_pin_read(BUTTON3) == 0)
            {
                //int push_num = get_first_element
                if (even_elements > 0)
                {
                    remove_element(&stack_head, &stack_head, get_first_element(stack_head));
                    even_elements -= 1;
                }
                
                
                //print_list(head);
                //front_and_peak(uneven_elements, even_elements);
                front_and_peak(uneven_elements, even_elements, kö_head, stack_head);
                nrfx_systick_delay_ms(1000);
            }



        }

    }
    
}




/*send_int(is_empty(head));

    new_line();
    int nummer;
    add_first(&head, &tail, 10);
    add_first(&head, &tail, 5);
    add_first(&head, &tail, 6);
    add_first(&head, &tail, 5);
    add_first(&head, &tail, 6);

    print_list(head);

    send_int(remove_element(&head, &tail, 5));

    print_list(head);

    nrf_gpio_pin_write(LED1,LED_ON);
    int loop = 1;
    while (loop = 1)
    {
        nrfx_systick_delay_ms(50);

        if (nrf_gpio_pin_read(BUTTON1) == 0)
        {
            nrf_gpio_pin_write(LED1,LED_OFF);
            loop = 0;
        }
    }*/