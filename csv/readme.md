解析csv(comma-separated-value)文件，有标准输入读取文件内容，输出解析结果

    line  |a |b |, |" |c |d |" |, |" |e |" |" |f |" |, |, |" |g |, |h |"

    sline |a |b |\0|" |c |d |\0|\0|" |e |" |f |\0|" |\0|\0|" |g |, |h |\0
           ^           ^              ^                 ^     ^
           |           |              |                 |     |
    field  0           1              2                 3     4
