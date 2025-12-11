#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <asn_application.h>

// include the headers for the 3 message types
#include "MIB.h"
#include "BCCH-DL-SCH-Message.h"
#include "DL-DCCH-Message.h"

extern asn_TYPE_descriptor_t asn_DEF_MIB;
extern asn_TYPE_descriptor_t asn_DEF_BCCH_DL_SCH_Message;
extern asn_TYPE_descriptor_t asn_DEF_DL_DCCH_Message;

// 1.Decoder for BCCH-BCH (MIB) 
MIB_t *decode_mib(const uint8_t *buffer, size_t size) {
    MIB_t *mib_ptr = NULL;

    asn_dec_rval_t rval = uper_decode_complete(
        NULL,
        &asn_DEF_MIB,
        (void **)&mib_ptr,
        buffer,
        size
    );

    if (rval.code != RC_OK) {
        fprintf(stderr, " BCCH-BCH (MIB) decoding failed at byte %zd.\n", rval.consumed);
        if (mib_ptr) ASN_STRUCT_FREE(asn_DEF_MIB, mib_ptr);
        return NULL;
    }
    printf(" BCCH-BCH (MIB) successfully decoded.\n");
    return mib_ptr;
}

// 2.Decoder for BCCH-DLSCH 
BCCH_DL_SCH_Message_t *decode_bcch_dlsch(const uint8_t *buffer, size_t size) {
    BCCH_DL_SCH_Message_t *msg_ptr = NULL;

    asn_dec_rval_t rval = uper_decode_complete(
        NULL,
        &asn_DEF_BCCH_DL_SCH_Message,
        (void **)&msg_ptr,
        buffer,
        size
    );

    if (rval.code != RC_OK) {
        fprintf(stderr, " BCCH-DLSCH decoding failed at byte %zd.\n", rval.consumed);
        if (msg_ptr) ASN_STRUCT_FREE(asn_DEF_BCCH_DL_SCH_Message, msg_ptr);
        return NULL;
    }

    printf(" BCCH-DLSCH container successfully decoded.\n");

    if (msg_ptr->message.present == BCCH_DL_SCH_MessageType_PR_c1) {
        BCCH_DL_SCH_MessageType__c1_PR type = msg_ptr->message.choice.c1.present;
        switch (type) {
            case BCCH_DL_SCH_MessageType__c1_PR_systemInformationBlockType1:
                printf(" -> Contained Payload: **SystemInformationBlockType1 (SIB1)**.\n");
                break;
            case BCCH_DL_SCH_MessageType__c1_PR_systemInformation:
                printf(" -> Contained Payload: **SystemInformation (Multiple SIBs)**.\n");
                break;
             default:
                printf(" -> Contained Payload: Unknown c1 message type.\n");
        }
    }
    return msg_ptr;
}


// 3.Decoder for DL-DCCH
DL_DCCH_Message_t *decode_dl_dcch(const uint8_t *buffer, size_t size) {
    DL_DCCH_Message_t *msg_ptr = NULL;

    asn_dec_rval_t rval = uper_decode_complete(
        NULL,
        &asn_DEF_DL_DCCH_Message,
        (void **)&msg_ptr,
        buffer,
        size
    );

    if (rval.code != RC_OK) {
        fprintf(stderr, " DL-DCCH decoding failed at byte %zd.\n", rval.consumed);
        if (msg_ptr) ASN_STRUCT_FREE(asn_DEF_DL_DCCH_Message, msg_ptr);
        return NULL;
    }

    printf(" DL-DCCH container successfully decoded.\n");

    if (msg_ptr->message.present == DL_DCCH_MessageType_PR_c1) {
        DL_DCCH_MessageType__c1_PR type = msg_ptr->message.choice.c1.present;

        printf(" -> Contained Message: ");
        switch (type) {
            case DL_DCCH_MessageType__c1_PR_rrcSetup:
                printf("**RRCResume**\n");
                break;
            case DL_DCCH_MessageType__c1_PR_rrcReconfiguration:
                printf("**RRCReconfiguration**\n");
                break;
            case DL_DCCH_MessageType__c1_PR_securityModeCommand:
                printf("**SecurityModeCommand**\n");
                break;
            case DL_DCCH_MessageType__c1_PR_rrcRelease:
                printf("**RRCRelease**\n");
                break;
            default:
                printf("Unknown/Unhandled Dedicated Message Type.\n");
        }
    }
    return msg_ptr;
}


//  Main Function
void cleanup_decoded_messages(MIB_t *mib, BCCH_DL_SCH_Message_t *bch_dl, DL_DCCH_Message_t *dcch) {
    if (mib) ASN_STRUCT_FREE(asn_DEF_MIB, mib);
    if (bch_dl) ASN_STRUCT_FREE(asn_DEF_BCCH_DL_SCH_Message, bch_dl);
    if (dcch) ASN_STRUCT_FREE(asn_DEF_DL_DCCH_Message, dcch);
    printf("\nMemory cleaned up.\n");
}

int main() {
   
    uint8_t mib_test_data[] = {0x1C, 0x00};
    uint8_t dlsch_test_data[] = {0x00, 0x00, 0x00, 0x00};
    uint8_t dcch_test_data[] = {0x01, 0x01, 0x01, 0x01};

    printf("--- Decoding MIB ---\n");
    MIB_t *mib_result = decode_mib(mib_test_data, sizeof(mib_test_data));

    printf("\n--- Decoding BCCH-DLSCH ---\n");
    BCCH_DL_SCH_Message_t *dlsch_result = decode_bcch_dlsch(dlsch_test_data, sizeof(dlsch_test_data));

    printf("\n--- Decoding DL-DCCH ---\n");
    DL_DCCH_Message_t *dcch_result = decode_dl_dcch(dcch_test_data, sizeof(dcch_test_data));

    cleanup_decoded_messages(mib_result, dlsch_result, dcch_result);

    return 0;
}
