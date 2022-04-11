variable "s3_bucket_names" {
  type = list
  default = [
    "comm-landing-assets",
    "commapp-backup",
    "commapp-blob",
    "commapp-test",
    "karol-comm-test",
  ]
}

resource "aws_s3_bucket" "comm_buckets" {
  count         = length(var.s3_bucket_names)
  bucket        = var.s3_bucket_names[count.index]
}