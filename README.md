# Cart3DDemo

this is wxn branch.
---
![image](https://github.com/wss/Cart3DDemo/assets/78208268/b136ddd4-38bc-45de-a3d0-4bcd64ae64da)


![QQ录屏20240313145456 -original-original](https://github.com/wss/Cart3DDemo/assets/78208268/f5deaddd-a1ce-42fe-bf7a-078b3510cebb)



![QQ录屏20240313150139 -original-original](https://github.com/wss/Cart3DDemo/assets/78208268/4b47af7c-50d0-4c7f-9288-1127bd44bd30)

# 移动模型
- 先把模型中心定在屏幕的五五开

![image](https://github.com/wss/Cart3DDemo/assets/78208268/50e03de5-8c2f-41a7-8250-ccce86e0e103)

- 使用公式即可完成


![QQ录屏20240319173154 -original-original](https://github.com/wss/Cart3DDemo/assets/78208268/bdb0e9c1-b9f6-42c9-9ded-594c853c781e)


我看了一下午，相关大佬的qopengl鼠标操作，他们是这样操作的：

右键是与一个z轴的旋转，左键是一个x轴+y轴的旋转，两者不能混到一起，也就是说z轴是一组，x轴和y轴是一组，
像meshlab那样的丝滑的操作，我猜测是：当模型 与 当初刚刚加载进来时的位置 产生了一定的角度后，会从x轴+y轴组合转化为z轴

他们都没有像meshlab那样的操作，反正qt时没有相关的接口，这需要一定的算法加持：

什么样的算法？当模型旋转到什么位置时，切换旋转轴的组合？这个需要思考的。

![QQ录屏20240321195925 -original-original](https://github.com/wss/Cart3DDemo/assets/78208268/6623bb7a-052a-409f-a217-f0f9c79132a1)
