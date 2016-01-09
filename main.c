//
//  main.c
//  
//
//  Created by Hank Lee on 7/16/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//
//  Given IYUV, produce 422
//
//  This program replicates chroma pixels to produce 422 format; it is designed to have quick
//  access of encoder's 422 encoding ability.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "420To422.h"

int main(int argc, char * argv[]) {
    int fd_rd;
    int fd_wr;
    
    uint8_t *y;
    uint8_t *u;
    uint8_t *v;
    uint32_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;

    char *output_file_name;
    
    uint8_t *frame;
    uint8_t *u_out;
    uint8_t *v_out;
    
    if (argc < 4)
    {
        printf("usage: %s [input yuv] [width] [height]\n", argv[0]);
        return -1;
    }

    output_file_name = "422.yuv";
    
    fd_rd = open(argv[1], O_RDONLY);
    fd_wr = open(output_file_name, O_WRONLY | O_CREAT, S_IRUSR);

    width = atoi(argv[2]);
    height = atoi(argv[3]);
    
    wxh = width * height;
    
    frame = malloc(wxh * 3 / 2);
    u_out = malloc(wxh / 2);
    v_out = malloc(wxh / 2);
    
    y = frame;
    u = y + wxh;
    v = u + wxh / 4;
    
    printf("Processing: ");
    
    while (1)
    {
        rd_sz = read(fd_rd, frame, wxh * 3 / 2);
            
        if (rd_sz == wxh * 3 / 2)
        {   
            expand
            (
                width,
                height,
                u_out,
                v_out,
                u,
                v
            );

            write(fd_wr, y,     wxh);
            write(fd_wr, u_out, wxh / 2);
            write(fd_wr, v_out, wxh / 2);
        }
        else
        {
            break;
        }
        
        fputc('.', stdout);
        fflush(stdout);
    }

    printf("Done\n");
    printf("Output file: %s\n", output_file_name);

    return 0;
}
