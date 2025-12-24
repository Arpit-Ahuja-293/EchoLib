c# Download

## Manual Download

equinox can be downloaded as a [PROS](https://pros.cs.purdue.edu/) template from the [releases](https://github.com/equinox/equinox/releases) tab in the equinox github repository.

## Depot Download

If you don't want to re-download equinox every time a new release comes out, we've set up a depot to make the updating process easier.

You can use the following commands to add the depot to your `pros-cli` installation.

```bash
pros c add-depot equinox https://raw.githubusercontent.com/equinox/equinox/depot/stable.json # adds equinox's stable depot
pros c apply equinox # applies latest stable version of equinox
```

To update equinox, all you have to do is run the following command:

```bash
pros c update
```

### Beta Depot

```{warning}
Beta versions of equinox may not be fully tested or documented. Use at your own risk.
```

If you'd like to use a beta version of equinox you can add our beta depot like so:

```bash
pros c add-depot equinox https://raw.githubusercontent.com/equinox/equinox/depot/beta.json # adds equinox's beta depot
```

## Further steps

Once you've downloaded equinox we recommend you take a look at our [tutorials](./tutorials/1_getting_started.md).
