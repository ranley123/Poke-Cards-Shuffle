/**
 * @file print_faro_val.h
 * @author Marwan Fayed
 * @last_rev 22/02/2019
 * 
 * @brief stacscheck-compliant output function for Faro Shuffle practical.
 */

#ifndef _PRINT_FARO_VAL_H_
#define _PRINT_FARO_VAL_H_


/**
 * @brief Enumerated types used to decide output for stacscheck tests.
 */
typedef enum stringplace {PREFIX_START, PREFIX_IN, PREFIX_OUT, CARD_VAL, SUFFIX} Stringplace;

/**
 * @brief Function to generate stacscheck-compliant output.
 * 
 * This function called once per data-item. There are (2+deck_size) calls
 *  needed to output a deck's data. For example, 52 cards consists of:
 *     - one call for output type (PREFIX_START, PREFIX_IN, PREFIX_OUT)
 *     - 52 calls for the card contents (CARD_VAL)
 *     - one call to terminate the output (SUFFIX)
 * EXAMPLE USAGE:
 *     print_faro_val("", PREFIX_IN); // outputs " IN: "
 *     print_faro_val(card_val, CARD_VAL); // eg. if card_val <-- "5H\0", outputs "5H "
 *     print_faro_val("", SUFFIX);    // OUTPUTS "EoD\n"
 * 
 * @param string A pointer to a string of data (valid w/ CARD_VAL, otherwise ignored).
 * @param output_type Enumerated type (above). Determines type of output. 
 *                    Only CARD_VAL outputs preceding string param.
 * @return void
 */
void print_faro_val(const char *string, enum stringplace output_type);



#endif