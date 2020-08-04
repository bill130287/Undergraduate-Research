
#ifndef _AWS_IOT_CUSTOMER_CERT_RTOS_H_
#define _AWS_IOT_CUSTOMER_CERT_RTOS_H_


#define AWS_IOT_ROOT_CA_CERT                                            \
"-----BEGIN CERTIFICATE-----\r\n"                                       \
"MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\r\n"  \
"yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\r\n"  \
"ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\r\n"  \
"U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\r\n"  \
"ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\r\n"  \
"aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\r\n"  \
"MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\r\n"  \
"ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\r\n"  \
"biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\r\n"  \
"U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\r\n"  \
"aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\r\n"  \
"nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\r\n"  \
"t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\r\n"  \
"SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\r\n"  \
"BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\r\n"  \
"rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\r\n"  \
"NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\r\n"  \
"BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\r\n"  \
"BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\r\n"  \
"aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\r\n"  \
"MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\r\n"  \
"p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\r\n"  \
"5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\r\n"  \
"WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\r\n"  \
"4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\r\n"  \
"hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\r\n"              \
"-----END CERTIFICATE-----"



#define AWS_IOT_DEVICE_CERT                                             \
"-----BEGIN CERTIFICATE-----\r\n"                                       \
"MIIDWjCCAkKgAwIBAgIVALN9uyFY8vDLucVT/NqpBOksTw+SMA0GCSqGSIb3DQEB\r\n"  \
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\r\n"  \
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xNjA2MTcwODM3\r\n"  \
"NTFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\r\n"  \
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCS3QUV80WdOX49fiSy\r\n"  \
"JoAgDTpeUrHc8stf3GWa1XAviBBXYQpjYmo0Tx9dBcl9oA5PT+s2ic60otAyYXIb\r\n"  \
"Chs4UVY7B2Jxauj+5T2T+bEvTbZ0ojQcv0bocL26v2chq+CPz5wugeyUffAlz22c\r\n"  \
"JT7SctzG4+vQC1WHxeLVoE0/tTzGiLi82m9OcSXh+njvWXg/VRZ+UgWfQPAe6qbR\r\n"  \
"tL8u0Jbe+VL0r+KDfdz49ZIbS9Nqua6zL2cL8wd1wZOQrhvu9BeIc5graYlGXCee\r\n"  \
"uNHFQqh1ESP3tm2+V1Ze3tEizP5fXG5Q6YtrFJubixFzOnwOHnGvmbRkkXhYQwKN\r\n"  \
"7QX3AgMBAAGjYDBeMB8GA1UdIwQYMBaAFAh+z0JCGiRun30G2ZiFACFI3c87MB0G\r\n"  \
"A1UdDgQWBBTD/Ka8GfWo3z2F5dd0wR8bsIRnITAMBgNVHRMBAf8EAjAAMA4GA1Ud\r\n"  \
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAivZJDXTK97H1n5x8/caxSSU5\r\n"  \
"q6oE1yUzHZAg1++EdI7crzqWWCwEGsvS4GSTyuwVlqwkr4dDkcj8ri2hZEStRCyC\r\n"  \
"uYrioBciEU/LsW0IS4RO4BqO5eIRerWwcGFP/jhPa5JuZRmBmts7wIIpJ60PBq9g\r\n"  \
"F3xqNNLRxEjjNPEkVUZRePsUyehkHaYs0h1lwmFsCwjEceyJmcjdykXeWEYhRZOf\r\n"  \
"UEk/cHizBUUoP8rMXdP7VBcf3/g46jcjbvRYV7uqcdqDiirxI+uLMEb5bIpx/pzj\r\n"  \
"Xwi1SNKgtXovRE0NrHt1b7XSYGfGEp0NaWoEgogcHFgV51gMd+OfixHyOxfDkA==\r\n"  \
"-----END CERTIFICATE-----"


#define AWS_IOT_PRIVATE_KEY                                             \
"-----BEGIN RSA PRIVATE KEY-----\r\n"                                   \
"MIIEogIBAAKCAQEAkt0FFfNFnTl+PX4ksiaAIA06XlKx3PLLX9xlmtVwL4gQV2EK\r\n"  \
"Y2JqNE8fXQXJfaAOT0/rNonOtKLQMmFyGwobOFFWOwdicWro/uU9k/mxL022dKI0\r\n"  \
"HL9G6HC9ur9nIavgj8+cLoHslH3wJc9tnCU+0nLcxuPr0AtVh8Xi1aBNP7U8xoi4\r\n"  \
"vNpvTnEl4fp471l4P1UWflIFn0DwHuqm0bS/LtCW3vlS9K/ig33c+PWSG0vTarmu\r\n"  \
"sy9nC/MHdcGTkK4b7vQXiHOYK2mJRlwnnrjRxUKodREj97ZtvldWXt7RIsz+X1xu\r\n"  \
"UOmLaxSbm4sRczp8Dh5xr5m0ZJF4WEMCje0F9wIDAQABAoIBADMqLQtopWgRD5n8\r\n"  \
"yGwIXbrM4PjbdnuzWocbEYrPsTXeAVNvy160equepR6TVY8eo92dyiRF/m2QC1iB\r\n"  \
"+m7RJoqIS7Jk8DbzOBkVZE6ZPtFsEZSwrdcWDG4OWQsmg5eHecSgX5kUSoexGGkT\r\n"  \
"yuwLTcejnKbt4MmqKTIUDuK95iu7QH5e88Mc81qqPXIPRzZfmrqT4E4/uL1GhFhx\r\n"  \
"tDxkioJ2/wmYpqXGadQvefwqHiM1SBCZCxUVJYyY+bPrpO22ucUAIgtpjjHoYqzh\r\n"  \
"+pgglm2gHeyif8RSGMhefPTeq5FPJsgMwxtKE/QJRzHrLHk7kGunB2Ex/iguXE/Q\r\n"  \
"4nffUYECgYEA1+a4dR9DWTpTtLYWMMwJaqyi9ouaCq8R9DHtBX68VOmhp34g9Kzr\r\n"  \
"NwwtG/WRuuA9eL9SyJTqfACnSYRmY3V1jYhyZaOjEx8T1d6yxipLogKp1Hl3muWS\r\n"  \
"rf8xsoes+UMGAgXswV9myCkamV8TjHi/XJ/rTCjO8fy8FKAv6gBOCJsCgYEAriPP\r\n"  \
"s7c8awcLxSu/wppbKc27sLKsa6InbmSUuE7s2zZGxy/IlB4Aad4BexjfJo3mOOB9\r\n"  \
"uxV55oolda4znwxhMg8HckH4mNUvnf9hLdq8rP/gowsz24RlFQW/gNIKjOLi4YnV\r\n"  \
"crp3pgl/WruiDf0U7/0Yj9EjB7fiQXl/EUd059UCgYAPoNvpXoH5i4dTpXqlvZ9Q\r\n"  \
"4X5KaoCUFWgvTQ3jP/FSFDdncHHiREIikfcR9wy9gk3w16iebGks4L87SyI+QNpp\r\n"  \
"jF77jITZdX5yFNTME3O2Hos8ni5SQBwGDFsEmV2kDX3514Pz23wNMSyDvaYknPj9\r\n"  \
"M3ZM5QdV7P2QYKgXQD5l0QKBgHlEuRTXKv0BmCHD+LOFmKzA987ybn46GymWY7cC\r\n"  \
"R5HU928pCI6VYgZXs0JNLMGFmejL9OL+7rgsRi/wk0RUc69PpgjchkmwVIu716n+\r\n"  \
"JNx5CK+iUoexaE8+hIEqRGyeaA9WVE2kK0R2YrkF57HEJ/uEjsFAjBuI48hi2qlm\r\n"  \
"0LPNAoGAYOGgQQcdhXINDR2jRQI/c2MqBr8Z/n8ls9GM/GSm6ygL1UKR+KC6YV+8\r\n"  \
"sgz79swWoGiGMfYluFxe9+LDe4e/ACPFL96I5sRk1LM4i9qe7YuRAAfhxkIWm+YV\r\n"  \
"M2JpnMWZY7DeL1HBK2qSwtAVdoP67pRbWzZpXHJv/DdkV/zRkd4=\r\n"              \
"-----END RSA PRIVATE KEY-----"

#endif

