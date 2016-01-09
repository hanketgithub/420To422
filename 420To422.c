//
//  420To422.c
//  420To422
//
//  Created by Hank Lee on 7/16/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//
//

#include <stdint.h>

int expand
(
          uint32_t width,
          uint32_t height,
          uint8_t *u_out,
          uint8_t *v_out,
    const uint8_t *u,
    const uint8_t *v
)
{
    int i = 0;
    int j = 0;
    
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width / 2; i++)
        {
            u_out[j * width / 2 + i] = u[(j / 2) * width / 2 + i];

            v_out[j * width / 2 + i] = v[(j / 2) * width / 2 + i];
        }
    }

    return 0;
}
