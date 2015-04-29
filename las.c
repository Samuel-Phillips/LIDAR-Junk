#include <inttypes.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define LAS_PACKED __attribute__((__packed__))
#define required
typedef int8_t      las_char_t;
typedef int16_t     las_short_t;
typedef int32_t     las_long_t;
typedef int64_t     las_llong_t;
typedef uint8_t     las_uchar_t;
typedef uint16_t    las_ushort_t;
typedef uint32_t    las_ulong_t;
typedef uint64_t    las_ullong_t;
typedef float       las_float_t;
typedef double      las_double_t;
#define LAS_PFc "%" PRId8
#define LAS_PFs "%" PRId16
#define LAS_PFl "%" PRId32
#define LAS_PFll "%" PRId64
#define LAS_PFuc "%" PRIu8
#define LAS_PFus "%" PRIu16
#define LAS_PFul "%" PRIu32
#define LAS_PFull "%" PRIu64
#define LAS_PFxc "%" PRIx8
#define LAS_PFxs "%" PRIx16
#define LAS_PFxl "%" PRIx32
#define LAS_PFxll "%" PRIx64
#define LAS_PFd "%g"
#define LAS_PFf "%f"

#define LAS_PFnc LAS_PFc "\n"
#define LAS_PFns LAS_PFs "\n"
#define LAS_PFnl LAS_PFl "\n"
#define LAS_PFnll LAS_PFll "\n"
#define LAS_PFnuc LAS_PFuc "\n"
#define LAS_PFnus LAS_PFus "\n"
#define LAS_PFnul  LAS_PFul "\n"
#define LAS_PFnull LAS_PFull "\n"
#define LAS_PFnxc  LAS_PFxc "\n"
#define LAS_PFnxs  LAS_PFxs "\n"
#define LAS_PFnxl  LAS_PFxl "\n"
#define LAS_PFnxll LAS_PFxll "\n"
#define LAS_PFnd  LAS_PFd "\n"
#define LAS_PFnf  LAS_PFf "\n"

typedef struct {
    unsigned gps_time_type: 1;
    unsigned waveform_data_packets_internal: 1;
    unsigned waveform_data_packets_external: 1;
    unsigned return_numbers_synth_gen: 1;
    unsigned wkt: 1;
    unsigned reserved: 11;
} las_global_encoding_t;

#define LAS_GLOBAL_ENCODING(dat) \
        (las_global_encoding_t){ \
            .gps_time_type = dat & 1, \
            .waveform_data_packets_internal = dat & 2, \
            .waveform_data_packets_external = dat & 4, \
            .return_numbers_synth_gen = dat & 8, \
            .wkt = 16, \
            .reserved = dat & ~(~0 << 5) \
        }
struct lasheader1_0 {
    required    las_char_t      signature[4];
                las_ulong_t     reserved;
                las_ulong_t     guid_1;
                las_ushort_t    guid_2;
                las_ushort_t    guid_3;
                las_uchar_t     guid_4[8];
    required    las_uchar_t     version_major;
    required    las_uchar_t     version_minor;
    required    las_char_t      system_identifier[32];
    required    las_char_t      generating_software[32];
    required    las_ushort_t    flight_date_julian;
    required    las_ushort_t    year;
    required    las_ushort_t    header_size;
    required    las_long_t      offset_to_data;
    required    las_long_t      number_of_vlrs;
    required    las_uchar_t     point_data_format_id;
    required    las_uchar_t     point_data_record_length;
    required    las_ulong_t     number_of_point_records;
    required    las_ulong_t     number_of_points_by_return[5];
    required    las_double_t    x_scale_factor;
    required    las_double_t    y_scale_factor;
    required    las_double_t    z_scale_factor;
    required    las_double_t    x_offset;
    required    las_double_t    y_offset;
    required    las_double_t    z_offset;
    required    las_double_t    max_x;
    required    las_double_t    min_x;
    required    las_double_t    max_y;
    required    las_double_t    min_y;
    required    las_double_t    max_z;
    required    las_double_t    min_z;
} LAS_PACKED;

struct lasheader {
    required    las_char_t      signature[4];
    required    las_ushort_t    file_source_id;
    required    las_ushort_t    global_encoding;
                las_ulong_t     proj_id_guid_1;
                las_ushort_t    proj_id_guid_2;
                las_ushort_t    proj_id_guid_3;
                las_uchar_t     proj_id_guid_4[8];
    required    las_uchar_t     version_major;
    required    las_uchar_t     version_minor;
    required    las_char_t      system_identifier[32];
    required    las_char_t      generating_software[32];
    required    las_ushort_t    file_creation_day_of_year;
    required    las_ushort_t    file_creation_year;
    required    las_ushort_t    header_size;
    required    las_long_t      offset_to_point_data;
    required    las_long_t      number_of_vlrs;
    required    las_uchar_t     point_data_record_format;
    required    las_uchar_t     point_data_record_length;
    required    las_ulong_t     legacy_number_of_point_records;
    required    las_ulong_t     legacy_number_of_points_by_return[5];
    required    las_double_t    x_scale_factor;
    required    las_double_t    y_scale_factor;
    required    las_double_t    z_scale_factor;
    required    las_double_t    x_offset;
    required    las_double_t    y_offset;
    required    las_double_t    z_offset;
    required    las_double_t    max_x;
    required    las_double_t    min_x;
    required    las_double_t    max_y;
    required    las_double_t    min_y;
    required    las_double_t    max_z;
    required    las_double_t    min_z;
    required    las_ullong_t    start_of_waveform_data_packet_record;
    required    las_ullong_t    start_of_first_evlr;
    required    las_ulong_t     number_of_evlrs;
    required    las_ullong_t    number_of_point_records;
    required    las_ullong_t    number_of_points_by_return[15];
} LAS_PACKED;
#undef required

typedef struct lasheader lasheader_t;

bool las_isv1_0(lasheader_t *header) {
    return header->version_major == 1 && header->version_minor == 0;
}

bool readlasheader(FILE *lasfile, lasheader_t *dest,
        las_global_encoding_t *ge) {
    size_t nread = fread(dest, sizeof *dest, 1, lasfile);
    if (0 != memcmp(dest->signature, "LASF", 4)) return false;
    if (las_isv1_0(dest)) return true;
    if (nread < 1) return false;
    *ge = LAS_GLOBAL_ENCODING(dest->global_encoding);
    if (ge->waveform_data_packets_external ==
            ge->waveform_data_packets_internal) {
        return false; // these bits are mutually exclusive
    }
    return true;
}

static void clean_string(char *out, const char *in, size_t len) {
    static const char rep[] = "\xef\xbf\xbd";
    size_t i = 0, j = 0;
    for (; i < len; i++) {
        if (isprint(in[i])) {
            out[j++] = in[i];
        } else {
            memcpy(out+j, rep, 3);
            j += 3;
        }
    }
    out[j++] = '\0';
}

void las_tell_header(FILE *lasfile) {
    lasheader_t header;
    las_global_encoding_t ge;
    char guid_string_clean[4 * 3 + 1];
    char system_identifier_clean[32 * 3 + 1];
    char generator_clean[32 * 3 + 1];
    if (!readlasheader(lasfile, &header, &ge)) {}// return;
    clean_string(guid_string_clean, header.proj_id_guid_4, 4);
    if (!las_isv1_0(&header)) {
        clean_string(system_identifier_clean, header.system_identifier, 32);
        clean_string(generator_clean, header.generating_software, 32);
        printf("Header information for file:\n"
                "Signature: %.4s\n"
                "Source ID: " LAS_PFnus
                "GPS time type: %s\n"
                "Waveform data packets: %s\n"
                "Return numbers WERE%s synthetically generated\n"
                "Coordinate reference system: %s\n"
                "Project ID GUID part 1: " LAS_PFnul
                "Project ID GUID part 2: " LAS_PFnus
                "Project ID GUID part 3: " LAS_PFnus
                "Project ID GUID part 4: { "
                    LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "
                    LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "LAS_PFuc" }"
                    " (%s)\n"
                "Version: "LAS_PFuc"."LAS_PFnuc
                "System Identifier: %.32s\n"
                "Generator: %.32s\n"
                "Created on day "LAS_PFus" of year "LAS_PFnus
                "Header size: 0x"LAS_PFnxs
                "Offset to point data: 0x"LAS_PFnxl
                "Number of VLRs: "LAS_PFnl
                "Point record data format: "LAS_PFnuc
                "Point record data length: "LAS_PFuc" byte(s)\n"
                "Number of point records (Legacy):\n"
                "\tReturn 1: "LAS_PFnul
                "\tReturn 2: "LAS_PFnul
                "\tReturn 3: "LAS_PFnul
                "\tReturn 4: "LAS_PFnul
                "\tReturn 5: "LAS_PFnul
                "Scale Factor: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Offset: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Max: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Min: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Start of waveform data packet record: 0x"LAS_PFnxll
                "Start of first EVLR: 0x"LAS_PFnxll
                "Number of EVLRs: "LAS_PFnul
                "Number of point records: "LAS_PFnull
                "Number of points by return:\n"
                "\tReturn 1: "LAS_PFnull
                "\tReturn 2: "LAS_PFnull
                "\tReturn 3: "LAS_PFnull
                "\tReturn 4: "LAS_PFnull
                "\tReturn 5: "LAS_PFnull
                "\tReturn 6: "LAS_PFnull
                "\tReturn 7: "LAS_PFnull
                "\tReturn 8: "LAS_PFnull
                "\tReturn 9: "LAS_PFnull
                "\tReturn 10: "LAS_PFnull
                "\tReturn 11: "LAS_PFnull
                "\tReturn 12: "LAS_PFnull
                "\tReturn 13: "LAS_PFnull
                "\tReturn 14: "LAS_PFnull
                "\tReturn 15: "LAS_PFnull
                ,
                header.signature,
                header.file_source_id,
                (ge.gps_time_type? "GPS Week Time"
                 : "Adjusted Standard GPS Time"),
                (ge.waveform_data_packets_internal? "Internal"
                 : "External"),
                (ge.return_numbers_synth_gen? "" : " NOT"),
                (ge.wkt? "WKT" : "GeoTIFF"),
                header.proj_id_guid_1,
                header.proj_id_guid_2,
                header.proj_id_guid_3,
                header.proj_id_guid_4[0],
                header.proj_id_guid_4[1],
                header.proj_id_guid_4[2],
                header.proj_id_guid_4[3],
                header.proj_id_guid_4[4],
                header.proj_id_guid_4[5],
                header.proj_id_guid_4[6],
                header.proj_id_guid_4[7],
                guid_string_clean,
                header.version_major, header.version_minor,
                system_identifier_clean,
                generator_clean,
                header.file_creation_day_of_year,
                header.file_creation_year,
                header.header_size,
                header.offset_to_point_data,
                header.number_of_vlrs,
                header.point_data_record_format,
                header.point_data_record_length,
                header.legacy_number_of_points_by_return[0],
                header.legacy_number_of_points_by_return[1],
                header.legacy_number_of_points_by_return[2],
                header.legacy_number_of_points_by_return[3],
                header.legacy_number_of_points_by_return[4],
                header.x_scale_factor,
                header.y_scale_factor,
                header.z_scale_factor,
                header.x_offset,
                header.y_offset,
                header.z_offset,
                header.max_x,
                header.max_y,
                header.max_z,
                header.min_x,
                header.min_y,
                header.min_z,
                header.start_of_waveform_data_packet_record,
                header.start_of_first_evlr,
                header.number_of_point_records,
                header.number_of_points_by_return[0],
                header.number_of_points_by_return[1],
                header.number_of_points_by_return[2],
                header.number_of_points_by_return[3],
                header.number_of_points_by_return[4],
                header.number_of_points_by_return[5],
                header.number_of_points_by_return[6],
                header.number_of_points_by_return[7],
                header.number_of_points_by_return[8],
                header.number_of_points_by_return[9],
                header.number_of_points_by_return[10],
                header.number_of_points_by_return[11],
                header.number_of_points_by_return[12],
                header.number_of_points_by_return[13],
                header.number_of_points_by_return[14]);
    } else {
        struct lasheader1_0 *oldh = (void*)&header;
        clean_string(system_identifier_clean, oldh->system_identifier, 32);
        clean_string(generator_clean, oldh->generating_software, 32);
        printf("Header information for file:\n"
                "Signature: %.4s\n"
                "GPS time type: %s\n"
                "Coordinate reference system: %s\n"
                "Project ID GUID part 1: " LAS_PFnul
                "Project ID GUID part 2: " LAS_PFnus
                "Project ID GUID part 3: " LAS_PFnus
                "Project ID GUID part 4: { "
                    LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "
                    LAS_PFuc", "LAS_PFuc", "LAS_PFuc", "LAS_PFuc" }"
                    " (%s)\n"
                "Version: "LAS_PFuc"."LAS_PFnuc
                "System Identifier: %.32s\n"
                "Generator: %.32s\n"
                "Flight date Julian: "LAS_PFnus
                "Year: "LAS_PFnus
                "Header size: 0x"LAS_PFnxs
                "Offset to data: 0x"LAS_PFnxl
                "Number of VLRs: "LAS_PFnl
                "Point data format ID: "LAS_PFnuc
                "Point record data length: "LAS_PFuc" byte(s)\n"
                "Number of point records:\n"
                "\tReturn 1: "LAS_PFnul
                "\tReturn 2: "LAS_PFnul
                "\tReturn 3: "LAS_PFnul
                "\tReturn 4: "LAS_PFnul
                "\tReturn 5: "LAS_PFnul
                "Scale Factor: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Offset: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Max: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                "Min: ("LAS_PFd", "LAS_PFd", "LAS_PFd")\n"
                ,
                oldh->signature,
                "GPS Week Time",
                "GeoTIFF",
                oldh->guid_1,
                oldh->guid_2,
                oldh->guid_3,
                oldh->guid_4[0],
                oldh->guid_4[1],
                oldh->guid_4[2],
                oldh->guid_4[3],
                oldh->guid_4[4],
                oldh->guid_4[5],
                oldh->guid_4[6],
                oldh->guid_4[7],
                guid_string_clean,
                oldh->version_major, header.version_minor,
                system_identifier_clean,
                generator_clean,
                oldh->flight_date_julian,
                oldh->year,
                oldh->header_size,
                oldh->offset_to_data,
                oldh->number_of_vlrs,
                oldh->point_data_format_id,
                oldh->point_data_record_length,
                oldh->number_of_points_by_return[0],
                oldh->number_of_points_by_return[1],
                oldh->number_of_points_by_return[2],
                oldh->number_of_points_by_return[3],
                oldh->number_of_points_by_return[4],
                oldh->x_scale_factor,
                oldh->y_scale_factor,
                oldh->z_scale_factor,
                oldh->x_offset,
                oldh->y_offset,
                oldh->z_offset,
                oldh->max_x,
                oldh->max_y,
                oldh->max_z,
                oldh->min_x,
                oldh->min_y,
                oldh->min_z);
    }
}

int main(int argc, char **argv) {
    FILE *f;
    if (argc > 1) {
        errno = 0;
        f = fopen(argv[1], "r");
        if (!f) {
            perror("las");
            exit(-1);
        }
        las_tell_header(f);
    } else {
        puts("Not enough arguments");
    }
    return 0;
}


