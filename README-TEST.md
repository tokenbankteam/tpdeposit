# tpdeposit编译部署

## 依赖环境

1. eosio.cdt --- branch: release/1.5.x 或以上
2. eosio.contract --- tag:  v1.5.2 或以上

## 编译

#### 1. 将tpdeposit目录放入eosio.contracts内。
#### 2. 编辑文件 eosio.contracts/CMakeLists.txt:

```
add_subdirectory(tpdeposit)
```
#### 3. 运行eosio.contracts/build.sh完成编译
 ```
 ./build.sh
 ```
 
 ## 部署
 
```
cleos -u 'https://kylin.eos.dfuse.io' system newaccount itokenpocket tokenflex222 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '20.0000 EOS' --stake-net '3.0000 EOS' --stake-cpu '20.0000 EOS'

cd build
cleos -u 'https://kylin.eos.dfuse.io' set contract tokenflex222 ./tokenflex -p tokenflex222
```


# tokenflex测试
## 授权
```
cleos -u 'https://kylin.eos.dfuse.io' set account permission tokenflex222 active '{"threshold": 1,"keys": [{"key": "EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8", "weight": 1}],"accounts": [{"permission":{"actor":"tokenflex222","permission":"eosio.code"},"weight":1}]}' owner -p tokenflex222@owner
```

### 创建测试帐号
```
cleos -u 'https://kylin.eos.dfuse.io' system newaccount itokenpocket tokenfletest EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '10.0000 EOS' --stake-net '5.0000 EOS' --stake-cpu '20.0000 EOS'
cleos -u 'http://kylin.meet.one:8888' push action eosio.token transfer '["itokenpocket", "tokenfletest", "100.0000 EOS", "30000,3"]' -p itokenpocket
cleos -u 'http://kylin.meet.one:8888' push action eosiotptoke1 transfer '["eosiotptoke1", "tokenfletest", "20000.0000 TPT", "30000,3"]' -p eosiotptoke1
cleos -u 'http://kylin.meet.one:8888' push action eosiotptoke2 transfer '["eosiotptoke2", "tokenfletest", "2000000.0000 TTP", "30000,3"]' -p eosiotptoke2

cleos -u 'https://kylin.eos.dfuse.io' system newaccount itokenpocket tokenfletes1 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '2.0000 EOS' --stake-net '2.0000 EOS' --stake-cpu '10.0000 EOS'
cleos -u 'http://kylin.meet.one:8888' push action eosio.token transfer '["itokenpocket", "tokenfletes1", "20.0000 EOS", "30000,3"]' -p itokenpocket
cleos -u 'http://kylin.meet.one:8888' push action eosiotptoke1 transfer '["eosiotptoke1", "tokenfletes1", "40000.0000 TPT", "30000,3"]' -p eosiotptoke1
cleos -u 'http://kylin.meet.one:8888' push action eosiotptoke2 transfer '["eosiotptoke2", "tokenfletes1", "2000000.0000 TTP", "30000,3"]' -p eosiotptoke2

```

## 添加交易对
```
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 startmarket '["1"]' -p tokenflex222
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 stopmarket '["1"]' -p tokenflex222
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 delmarket '["1"]' -p tokenflex222
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addmarket '["0.0000 EOS", "eosiotptoke1", "0.0000 TPT", "5", "0"]' -p tokenflex222
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addmarket '["0.0000 EOS", "eosiotptoke2", "0.0000 TTP", "10", "0"]' -p tokenflex222
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 updmarket '["0", "0.0000 EOS", "eosiotptoke1", "0.0000 TPT", "5", "0"]' -p tokenflex222

```
## 查询
```
## 查询市场信息
cleos -u 'https://kylin.eos.dfuse.io' get table tokenflex222 tokenflex222 market

cleos -u 'https://kylin.eos.dfuse.io' get table tokenflex222 tokenflex222 marketshare -L itokenpocket

## 查询当前tokenfletest帐号余额信息
cleos -u 'https://kylin.eos.dfuse.io' get table tokenflex222 tokenflex222 flexfund --index 2 --key-type name -L tokenfletest -l 20

```
## 部署TTP
```
cleos -u 'https://kylin.eos.dfuse.io' system newaccount itokenpocket eosiotptoke2 EOS61Lv9AArofgBUhE4JKtJ5zJrLdRbNBwgPc5sWsxMNT6HtNm5py EOS8gE7XgUVLmF8CN9CCixNaVGFzbxvagVdMm6pqP47eMpuRMUDx8 --buy-ram '10.0000 EOS' --stake-net '3.0000 EOS' --stake-cpu '10.0000 EOS'

cd build
cleos -u 'https://kylin.eos.dfuse.io' set contract eosiotptoke2 ./eosio.token -p eosiotptoke2
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke2 create '["eosiotptoke2", "400000000.0000 TTP"]' -p eosiotptoke2
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke2 issue '["eosiotptoke2", "400000000.0000 TTP", ""]' -p eosiotptoke2
```
## 充值
```
cleos -u 'https://kylin.eos.dfuse.io' push action eosio.token transfer '["tokenfletest", "tokenflex222", "4.0000 EOS", "deposit:1"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke1 transfer '["tokenfletest", "tokenflex222", "4000.0000 TPT", "deposit:1"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke2 transfer '["tokenfletest", "tokenflex222", "140000.0000 TTP", "deposit:1"]' -p tokenfletest

cleos -u 'https://kylin.eos.dfuse.io' push action eosio.token transfer '["tokenfletes1", "tokenflex222", "3.0000 EOS", "deposit:1"]' -p tokenfletes1
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke1 transfer '["tokenfletes1", "tokenflex222", "3000.0000 TPT", "deposit:1"]' -p tokenfletes1
cleos -u 'https://kylin.eos.dfuse.io' push action eosiotptoke2 transfer '["tokenfletes1", "tokenflex222", "200000.0000 TTP", "deposit:1"]' -p tokenfletes1
```

## 添加减少流动性
```
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addliq '["tokenfletest", "0.1000 EOS", "eosiotptoke1", "1000.0000 TPT"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 removeliq '["tokenfletest", "0.0500 EOS", "eosiotptoke1", "500.0000 TPT"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addliq '["tokenfletest", "0.5000 EOS", "eosiotptoke2", "11000.0000 TTP"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addliq '["tokenfletes1", "0.1000 EOS", "eosiotptoke1", "1000.0000 TPT"]' -p tokenfletes1
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 addliq '["tokenfletes1", "0.4500 EOS", "eosiotptoke2", "11000.0000 TTP"]' -p tokenfletes1

```

## 兑换
```
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 tswapb '["tokenfletest", "eosiotptoke1", "100.0000 TPT"]' -p tokenfletest
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 bswapt '["tokenfletes1", "0.1000 EOS", "eosiotptoke1", "4,TPT"]' -p tokenfletes1
cleos -u 'https://kylin.eos.dfuse.io' push action tokenflex222 tswapt '["tokenfletes1", "eosiotptoke2", "2100.0000 TTP", "eosiotptoke1", "4,TPT"]' -p tokenfletes1

```
