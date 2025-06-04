/*
this could be done more easily with some built-in with some built in functions, but the tutorial server is DOWN right now and I simply don't know how to do it!!!
*/

int main() {
// PART 1, C-style (https://www.youtube.com/watch?v=8SUkrR7ZfTA)
#ifdef 1_1
    // 1.1, Don't be too clever
    if (Armed ? Vcnt >= threshold : Vcnt <= threshold) 
    /* check if exceed threshold then do something */ ;
    // the comment and the code don't agree
    if (Armed && Vcnt >= Threshold || !Armed && Vcnt <= Threshold) ;
    // same logic, clear intent
#endif
#ifdef 1_2
    // 1.2 Don't be too dumb
    char blank[] = " "; /* define a blank */
    if (strncmp(str, blank, 1) != 0) {
        if (
            (strcmp(str, "0") >= 0) 
            && (strcmp(str, "9") <= 0)
        ) {
            (void) strncpy(str1, str, 1);
        }
    }
    // same as:
    if (str[0] != ' ') {
        if (isdigit(str[0])) {
            str1[0] = str[0];
        }
    }
#endif
#ifdef 1_3 
    // 1.3 Keep it simple (stupid)
    char *remove_spaces(char *data) {
        char *ptr; 
        int lenght = strlen(data);

        ptr = data;
        while ( (ptr = strpbrk(data, " " )) ) {
            memmove(ptr, ptr + 1, strlen(ptr) + 1);
            length--;
        }
        /* Terminate at the new string length */
        data[length] = '\0';
        return(data);
    }
    // copy in-place:
    char *remove_spaces(char *data) {
        char *in, *out;
        for (in = out = data; *in != '\0'; in++)
            if (*in != ' ')
                *out++ = *in;
        *out = '\0';
        return data;
    }
#endif
#ifdef 1_4_1
    // 1.4.1 Know your language
    if (i == 0) c = '0';
    if (i == 0) c = '1';
    if (i == 0) c = '2';
    if (i == 0) c = '3';
    if (i == 0) c = '4';
    if (i == 0) c = '5';
    if (i == 0) c = '6';
    if (i == 0) c = '7';
    if (i == 0) c = '8';
    if (i == 0) c = '9';
    // let the computer do the repetition part:
    if (i >= 0 && i <= 9 )
        c = i + '0';
#endif
#ifdef 1_4_2
    // 1.4.2 
    int make_eight_bits(int q) {
        for(int i = 15; i >= 8; i--)
            if (q >= pow(2, i))
                q -= pow(2, i);
        return (q);
    }
    // use bitwise operators instead:
    int make_eight_bits(int q) {
        return q & 0xFF;
    }
#endif
#ifdef 1_5
    // 1.5, Don't mix logical and arithmetic operators
    /* Interchange 2 bytes of a short */
    #define flip2(a) \
        (((a) & 0xFF) << 8 + ((a) & 0xFF00) >> 8)
    // consider the effect of doing that to a negative number
    // consider the relative precedence of the operators
    #define flip2(a) \
        ((a) << 8 | ((a) >> 8) & 0xFF)
    // remember: machine-independent code is wrong on all machines
#endif
#ifdef 1_6
    // 1.6, Avoid macros in C/C++
    #define isdigit(c) ((c) >= '0' && (c) <= '9')
    // this example has a bug:
    while (isdigit(*--jext)) {
        if (*jext != '9') {
            (*jext)++;
            break;
        }
    }
    *jext = '0';
#endif
#ifdef 1_7
    // 1.7, Don't sacrifice clarity for efficiency
    #define fast_memcpy(d, s, n)                                                    \
    {                                                                               \
        register size_t nn = (size_t)(n);                                           \
        if (nn >= breakeven_point)                                                  \
            memcpy((d), (s), nn);                                                   \
        else if (nn > 0) { /* proc call overhead is worth only for large strings */ \
            register char *dd;                                                      \
            register const charr *ss;                                               \
            for (ss=(s), dd=(d); nn > 0; nn--)                                      \
                *dd++ = *ss++;                                                      \
        }                                                                           \
    }
    // modern compilers are smarter than you are
#endif
#ifdef 1_8
    // 1.8, Know the bad features and pitfalls of your language
    char *combine(char *s, char *t) /* strcat implementation */
    /* Return a char pointer to caller */
    {
        int x, y;
        char r[100];
        strcpy(r, s);
        y = strlen(r);
        for (x = y; *t != '\0'; ++x) /* count x starting at x=y */
            r[x] = *t++;             /* read byte from t into r */
        r[x] = '\0';                 /* tack on NULL */
        return(r);                   /* return the pointer to the internal array */
    } // this example is from the worst book on C programming ever written
#endif
#ifdef 1_9
    // 1.9, Use the idioms of your language
    for (i = 0; i <= n - 1; ) array[i++] = 0;
    for (i = 0; i < n; )      array[i++] = 0;
    for (i = n; --i >= 0; )   array[i++] = 0;
    for (i = 0; i < n; i++)   array[i] = 0;
    // example 1:
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    // example 2:
    do {
        c = getchar();
        putchar(c);
    } while (c != EOF);
    // there's a subtle bug in that example, instead do this:
    while ((c = getchar()) != EOF) 
        putchar(c);
#endif
#ifdef 1_10
    // 1.10, Test programs at their boundaries
    char *remove_trailing_asterisk(char *data) {
        int i;
        /* Should the test here be i >= 0 ?? */
        // Double check that by using "*" as input data
        for (i = strlen(data) - 1; i > 0; i--) {
            if (data[i] == '*')
                data[i] = '\0';
        }
        return(data);
    }
#endif
#ifdef 1_11_1
    // 1.11.1, Program defensively, check parameters
    float st_stdev(float *buf, int M) {
        double stdev = 0;
        int m;
        float mean = st_mean(buf, M);
        for (m = 0; m < M; m++)
            stdev += (buf[m] - mean) * (buf[m] - mean);
        return sqrt(stdev/(M - 1)); // what if M == 1, what if M == 0?
    } // defend the code against the stupidity of your users (could be you also in another part of the code)
#endif
#ifdef 1_11_2
    // 1.11.2, Program defensively, never trust input
    void get_input(size_t SIZE) {
        static char number[SIZE];
        gets(number);
        if (number[SIZE - 1] != '\0') {
            puts("Overflow!");
            exit(1);
        }
    }
    // another example:
    char post_string[1024];
    content_length = atoi(getenv("CONTENT_LENGTH"));
    cin.read( post_string, content_length );
    // "Always validate all your inputs -- the world outside your function should be treated as hostile and bent on your destruction." - Howard & LeBlanc, "Writing Secure Code"
#endif
#ifdef 1_11_3
    // 1.11.3, Program defensively, watch for overflow
    int input_filter(void **data, char *params) {
        char fname[64], tmp[256], rotunits_txt;
        if (sscanf(params, "%s %i %c", fname, &order, &rotunits_txt) != 3) {}
    }
    // another example:
    char s[64];
    sprintf(s, "There's no box called '%s' in this schematic type.", name);
#endif
#ifdef 1_12
    // 1.12, Every time you make a decision, do something
    if (argc == 3) 
        if ((fin = fopen(argv[1], "r")) != NULL)
            if ((fout = fopen(argv[2], "w")) != NULL) {
                while ((c = getc(fin)) != EOF)
                    putc(c, fout);
            } else 
                printf("Can't open output file %s", argv[2]);
        else 
            printf("Can't open input file %s", argv[1]);
    else
        printf("Usage: cp inputfile outputfile\n");
        // too many nested conditions, instead consider:
    if (argc != 3)
        printf("Usage: cp inputfile outputfile\n");
    else if ((fin = fopen(argv[1], "r")) == NULL)
        printf("Can't open input file %s", argv[1]);
    else if ((fout = fopen(argv[2], "w")) == NULL) {
        
        printf("Can't open output file %s", argv[2]);
        fclose(fin);
    } else {
        while ((c = getc(fin)) != EOF)
            putc(c, fout);
        fclose(fin);
        fclose(fout);
    } 
#endif
#ifdef 1_13
    // 1.13, Put regularity in control flow, irregularity in data
    if (!(n = append_char(ch++, 50, 5))) return(false); /* height will be 10 */
    if (!(n = append_char(ch++, 50, 10))) return(false); /* force height=10 */
    /* line 2 is 10 high, 3 chars, ... */
    if (!(n = append_char(ch++, 1, 1))) return(false);
    if (!(n = append_char(ch++, 98, 1))) return(false);
    // ...
    return(true);
    // instead of duplicating code consider doing this:
    static int xy[] = {
        50, 5, /* height will be 10 */
        50, 10, /* force height=10 */
        1, 1, /* line 2 is 10 high, 3 chars, ... */
        98, 1,
        // ... 
        -1, -1,
    }
    for (i = 0; xy[i] != -1; i +=2)
        if ((n = append_char(ch++, xy[i], xy[i + 1]) == 0)
            return false;
    return true;
#endif 
#ifdef MISC
    // Miscelaneous examples
    // a. Make sure the comments fit the code
    void dictionary::insert( char *w );
    /* returns 1 if w in dic otherwise returns 0 */

    // b. Don't echo in the comments what the code says
    /* ignore the SIGHUP signal */
    (void)signal(SIGHUP, SIG_IGN);
    /* ignore the SIGTERM signal */
    (void)signal(SIGTERM, SIG_IGN);
    // ...
    // maybe the programmer is being paid by the line?
    // another example:
    /* return SUCCESS */
    return(SUCCESS);

    // c. Don't document bad code, rewrite it
    strtod(buf, &rem); /* parse the number */
    unputstr(rem);     /* put rest back for later */
    /* printf("unputstr [%s], buf [%s]\n", rem, buf); */
    if (rem == buf) {   /* it wasn't a valid number at all */
        buf[1] = 0;     /* so return one character as token */
        retc = buf[0];  /* character is its own type */
    } else {            /* some prefix was a number */
        rem[0] = 0;     /* so truncate where failure started */
        retc = '0';     /* number */
    }
#endif

// PART 2, C++ idioms

}
 