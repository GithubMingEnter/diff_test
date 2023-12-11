





数组转换为protobuf

```cpp

prt.mutable_nodes()->Add()->set_node_id(data.nodes[i].node_id);
```

预先分配内存

```cpp

prt.mutable_link_node_ids()->Resize(data.link_node_ids.size(),0);
    for(size_t i=0;i<data.link_node_ids.size();++i)
    {
        prt.mutable_link_node_ids()->Set(i,data.link_node_ids[i]);
    }
```
