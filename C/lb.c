//
//  lb.c
//  test-Programs
//
//  Created by vidua on 11/14/19.
//  Copyright © 2019 Vivek Dua. All rights reserved.
//

//    Late binding is an infra where the application code offloads the late binding of different network events
//    and its subsequent action to an infra piece of software thereby making the application code clean and abstracted.
//    It scales well with evolving states needing various events before an action is taken.
//    It is specifically useful in async infrastructure where network events can come in any order. Hence,
//    rather than letting application code go messy by coding up all different if checks for all network events,
//    it makes sense to code up a LB infra which handles this separate from the application code.



#include <stdio.h>
#include <stdlib.h>


typedef void (*ACTIONFUNC)(void *context, void *arg);

typedef enum { FALSE, TRUE } boolean;

typedef enum _lb_states {
    _SSM_DISBALED,
    MAX_LB_STATES
} lb_state_type;

typedef enum {
    LB_STATE_CONFIG,
    LB_STATE_OPER,
    
    LB_STATE_MAX
} lb_state_event;

typedef struct {
    lb_state_type _type;
    boolean       _states[LB_STATE_MAX];
    
    ACTIONFUNC    _func;
    void*         _arg;
} lb_state;

typedef struct {
    lb_state  _states[MAX_LB_STATES];
    void*     _context;
} lb_context;

// APIs
// Init the LB in a context
lb_context* init_lb_context (void *context) {
    lb_context* ctx = calloc(1, sizeof(lb_context));
    ctx->_context = context;
    return ctx;
}

void set_lb_state (lb_context* ctx, lb_state_type type,
                    ACTIONFUNC func, void *arg)
{
    ctx->_states[type]._type = type;
    ctx->_states[type]._func = func;
    ctx->_states[type]._arg   = arg;
}

void set_lb_state_user (lb_context* ctx, lb_state_type type,
                        lb_state_event event, boolean enable_disable) {
    // add or create a new lb_state
    ctx->_states[type]._type = type;
    ctx->_states[type]._states[event] = enable_disable;
    
    // if all enabled, then call the action-func-ptr
    boolean enable = TRUE;
    for (int i = 0; i < LB_STATE_MAX; i++) {
        if (ctx->_states[type]._states[i] == FALSE) {
            enable = FALSE;
            break;
        }
    }
    if (enable) {
        // call the action
        ctx->_states[type]._func(ctx->_context, ctx->_states[type]._arg);
    }
    
}
